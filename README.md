# Train Track Crossing Simulation

Este projeto simula a travessia de carros e trens em um cruzamento de trilhos utilizando o FreeRTOS.

## Estrutura do Projeto

    src/: Contém o código-fonte principal do projeto.
    FreeRTOSv10.0.1/: Contém os arquivos de origem do FreeRTOS.
    CMakeLists.txt: Arquivo de configuração do CMake.

## Pré-requisitos

* CMake 3.5 ou superior
* Visual Studio 2022

## Configuração do Ambiente

1. Clone este repositório:

```bash
git clone https://github.com/seu-usuario/train-track-crossing-simulation.git
cd train-track-crossing-simulation
```
2. Certifique-se de que o FreeRTOS está na estrutura de pastas correta:

    train-track-crossing-simulation/
    ├── FreeRTOSv10.0.1/
    ├── src/
    ├── CMakeLists.txt
    └── ...

## Construindo o Projeto
### Usando CMake e Visual Studio

1. Crie uma pasta build na raiz do projeto e navegue até ela:

```bash
if (Test-Path -Path "build") {
    Remove-Item -Recurse -Force "build/*"
} else {
    New-Item -ItemType Directory -Path "build"
}

cd build
```

2. Gere os arquivos do projeto para Visual Studio:

```bash
cmake -G "Visual Studio 17 2022" ..
```
    
3. Abra o arquivo de solução gerado (TrainTrackCrossingSimulation.sln):
    * Navegue até a pasta build e procure pelo arquivo TrainTrackCrossingSimulation.sln.
    * Clique duas vezes no arquivo para abri-lo no Visual Studio.

4. No Visual Studio:
    * Abra o Solution Explorer. Você pode encontrá-lo no menu View -> Solution Explorer.
    * No Solution Explorer, selecione a solução TrainTrackCrossingSimulation.
    * Clique com o botão direito sobre a solução e selecione Build para compilar o projeto.

## Detalhes do Arquivo CMakeLists.txt

O arquivo CMakeLists.txt está configurado para incluir os diretórios e arquivos necessários do FreeRTOS e do projeto principal. Certifique-se de que todos os caminhos estão corretos conforme a estrutura do seu projeto.

    cmake_minimum_required(VERSION 3.5)
    project(TrainTrackCrossingSimulation)
    
    # Include FreeRTOS source and port files
    include_directories(FreeRTOSv10.0.1/FreeRTOS/Source/include 
                        FreeRTOSv10.0.1/FreeRTOS/Source/portable/MSVC-MingW 
                        FreeRTOSv10.0.1/FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace/include 
                        FreeRTOSv10.0.1/FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace)
    
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

Certifique-se de seguir estas etapas cuidadosamente para configurar e compilar o projeto corretamente. Se encontrar algum problema, verifique novamente os passos e as configurações do arquivo CMakeLists.txt.

### Usage

* The system will start simulating trains and cars crossing the intersection.
* Trains and cars will be displayed with their respective IDs and actions (e.g., arrival, crossing).
* The gate status and semaphore lights will be updated accordingly.
