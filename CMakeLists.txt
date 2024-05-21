cmake_minimum_required(VERSION 3.5)
project(TrainTrackCrossingSimulation)


# Include FreeRTOS source and port files
include_directories(
    FreeRTOSv10.0.1/FreeRTOS/Source/include 
    FreeRTOSv10.0.1/FreeRTOS/Source/portable/MSVC-MingW 
    FreeRTOSv10.0.1/FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace/include 
    FreeRTOSv10.0.1/FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace/config 
    FreeRTOSv10.0.1/FreeRTOS/Demo/WIN32-MSVC
)

# Add your source files
set(SOURCE_FILES 
    src/main.c
)

# Add FreeRTOS source files
set(FREERTOS_SOURCE_FILES
    FreeRTOSv10.0.1/FreeRTOS/Source/croutine.c
    FreeRTOSv10.0.1/FreeRTOS/Source/event_groups.c
    FreeRTOSv10.0.1/FreeRTOS/Source/list.c
    FreeRTOSv10.0.1/FreeRTOS/Source/queue.c
    FreeRTOSv10.0.1/FreeRTOS/Source/tasks.c
    FreeRTOSv10.0.1/FreeRTOS/Source/timers.c
    FreeRTOSv10.0.1/FreeRTOS/Source/portable/MemMang/heap_4.c
    FreeRTOSv10.0.1/FreeRTOS/Source/portable/MSVC-MingW/port.c
)

# Create an executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${FREERTOS_SOURCE_FILES})

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Set optimization level
set(CMAKE_C_FLAGS_RELEASE "-O3")

# Link any required libraries
target_link_libraries(${PROJECT_NAME} m)
