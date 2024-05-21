#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define STANDARD "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"

QueueHandle_t carQueue; // Car queue
QueueHandle_t trainQueueCGJP; // Train queue going CG to JP
QueueHandle_t trainQueueJPCG; // Train queue going JP to CG

SemaphoreHandle_t mutexCGJP; // Mutex for the train queue going CG to JP
SemaphoreHandle_t mutexJPCG; // Mutex for the train queue going JP to CG
SemaphoreHandle_t gateSemaphore; // Semaphore to control the gate opening and closing

void car(void *pvParameters) {
    int carID = *((int *)pvParameters);

    while (1) {
        // Check if the gate is open
        printf("Car %d arrived at the gate.\n", carID);
        if (xSemaphoreTake(gateSemaphore, pdMS_TO_TICKS(100)) == pdTRUE) {
            printf("Car %d crossing the intersection.\n", carID);
            vTaskDelay(pdMS_TO_TICKS(1000)); // Simulate crossing time
            printf("Car %d passed the intersection.\n", carID);
            xSemaphoreGive(gateSemaphore); // Release the semaphore after the car passes
        } else {
            printf("Car %d waiting at the gate.\n", carID);
        }

        // Add car ID to the queue to maintain the arrival order
        xQueueSend(carQueue, &carID, portMAX_DELAY);

        // Check if this car is next in line
        int nextCarID;
        if (xQueueReceive(carQueue, &nextCarID, 0) == pdPASS) {
            if (nextCarID != carID) {
                // Car is not next in line, put it back into the queue
                xQueueSendToFront(carQueue, &nextCarID, 0);
            }
        }

        carID++;
        vTaskDelay(pdMS_TO_TICKS((rand() % 100 + 151))); // Simulate time between cars
    }
}



// Function for the behavior of the train task - direction CG to JP
void trainFromCGToJP(void *pvParameters) {
    int trainID = *((int *)pvParameters);
    while (1) {
        // Determine the direction message based on the train direction
        char *directionMessage = "From CG to JP";

        printf("Train %d approaching the crossing (%s).\n", trainID, directionMessage);

        xSemaphoreTake(mutexCGJP, portMAX_DELAY); // Acquire the mutex to access the queue
        xQueueSend(trainQueueCGJP, &trainID, portMAX_DELAY); // Push train ID into the queue
        if (uxQueueMessagesWaiting(trainQueueCGJP) == 1 && uxQueueMessagesWaiting(trainQueueJPCG) == 0) {
            printf("Gate closed: |X-X-X|\n");
            printf("Semaphore: [" RED "●" STANDARD "] [●]\n"); // Red light for semaphore
            xSemaphoreTake(gateSemaphore, portMAX_DELAY); // Close the gate if a train approaches while there are no other trains
        }
        xSemaphoreGive(mutexCGJP); // Release the mutex for the queue

        // Wait for its turn in the queue
        while (uxQueuePeek(trainQueueCGJP, &trainID) != pdPASS || trainID != *((int *)pvParameters)) {
            vTaskDelay(pdMS_TO_TICKS(50)); // Wait a bit before checking again
        }

        printf("Train %d crossing the intersection (%s).\n", trainID, directionMessage);
        vTaskDelay(pdMS_TO_TICKS(3000)); // Simulate crossing time
        printf("Train %d passed the intersection (%s).\n", trainID, directionMessage);

        xSemaphoreTake(mutexCGJP, portMAX_DELAY); // Acquire the mutex to access the queue
        xQueueReceive(trainQueueCGJP, &trainID, portMAX_DELAY); // Pop train ID from the queue
        if (uxQueueMessagesWaiting(trainQueueCGJP) == 0 && uxQueueMessagesWaiting(trainQueueJPCG) == 0) {
            printf("Gate open: |     |\n");
            printf("Semaphore: [●] [" GREEN "●" STANDARD "]\n"); // Green light for semaphore
            xSemaphoreGive(gateSemaphore); // Open the gate if there are no trains
        }
        xSemaphoreGive(mutexCGJP); // Release the mutex for the queue

        trainID++;
        vTaskDelay(pdMS_TO_TICKS((rand() % 75 + 151))); // Simulate time between trains
    }
}

// Function for the behavior of the train task - direction JP to CG
void trainFromJPToCG(void *pvParameters) {
    int trainID = *((int *)pvParameters);
    while (1) {
        // Determine the direction message based on the train direction
        char *directionMessage = "From JP to CG";

        printf("Train %d approaching the crossing (%s).\n", trainID, directionMessage);

        xSemaphoreTake(mutexJPCG, portMAX_DELAY); // Acquire the mutex to access the queue
        xQueueSend(trainQueueJPCG, &trainID, portMAX_DELAY); // Push train ID into the queue
        if (uxQueueMessagesWaiting(trainQueueJPCG) == 1 && uxQueueMessagesWaiting(trainQueueCGJP) == 0) {
            printf("Gate closed: |X-X-X|\n");
            printf("Semaphore: [" RED "●" STANDARD "] [●]\n"); // Red light for semaphore
            xSemaphoreTake(gateSemaphore, portMAX_DELAY); // Close the gate if a train approaches while there are no other trains
        }
        xSemaphoreGive(mutexJPCG); // Release the mutex for the queue

        // Wait for its turn in the queue
        while (uxQueuePeek(trainQueueJPCG, &trainID) != pdPASS || trainID != *((int *)pvParameters)) {
            vTaskDelay(pdMS_TO_TICKS(50)); // Wait a bit before checking again
        }

        printf("Train %d crossing the intersection (%s).\n", trainID, directionMessage);
        vTaskDelay(pdMS_TO_TICKS(3000)); // Simulate crossing time
        printf("Train %d passed the intersection (%s).\n", trainID, directionMessage);

        xSemaphoreTake(mutexJPCG, portMAX_DELAY); // Acquire the mutex to access the queue
        xQueueReceive(trainQueueJPCG, &trainID, portMAX_DELAY); // Pop train ID from the queue
        if (uxQueueMessagesWaiting(trainQueueJPCG) == 0 && uxQueueMessagesWaiting(trainQueueCGJP) == 0) {
            printf("Gate open: |     |\n");
            printf("Semaphore: [●] [" GREEN "●" STANDARD "]\n"); // Green light for semaphore
            xSemaphoreGive(gateSemaphore); // Open the gate if there are no trains
        }
        xSemaphoreGive(mutexJPCG); // Release the mutex for the queue

        trainID++;
        vTaskDelay(pdMS_TO_TICKS((rand() % 75 + 151))); // Simulate time between trains
    }
}


int main() {
    srand(time(NULL));

    // Create the queues for train and car queues
    carQueue = xQueueCreate(6, sizeof(int)); // Queue size is 6
    trainQueueCGJP = xQueueCreate(5, sizeof(int)); // Queue size is 5
    trainQueueJPCG = xQueueCreate(3, sizeof(int)); // Queue size is 3

    // Create the semaphores
    mutexCGJP = xSemaphoreCreateMutex();
    mutexJPCG = xSemaphoreCreateMutex();
    gateSemaphore = xSemaphoreCreateMutex();

    // Create tasks for the trains and cars
    int *carID = (int *)malloc(sizeof(int));
    *carID = 1;
    xTaskCreate(car, "Car", 2048, (void *)carID, 1, NULL);

    int *trainIDFromCGToJP = (int *)malloc(sizeof(int));
    *trainIDFromCGToJP = 1;
    xTaskCreate(trainFromCGToJP, "Train_CG_JP", 2048, (void *)trainIDFromCGToJP, 2, NULL); // High priority for trains

    int *trainIDFromJPToCG = (int *)malloc(sizeof(int));
    *trainIDFromJPToCG = 1;
    xTaskCreate(trainFromJPToCG, "Train_JP_CG", 2048, (void *)trainIDFromJPToCG, 2, NULL); // High priority for trains

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    return 0;
}
