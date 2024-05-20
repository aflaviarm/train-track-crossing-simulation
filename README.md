Introduction

This project implements a simulated railway crossing system using FreeRTOS. It consists of trains traveling between two directions (JP to CG and CG to JP) and cars that cross the intersection. The system controls the opening and closing of the gate and manages the passage of trains and cars through the intersection.
Features

    Train Management: Trains travel between two directions, and the system ensures safe crossing through the intersection.
    Car Management: Cars arrive at the gate, wait if it's closed, and cross the intersection when it's open.
    Gate Control: The gate opens and closes to allow the passage of trains and cars.
    Semaphore System: A semaphore system controls the gate opening and closing, with visual indication of the gate status (open/closed) and semaphore lights (red/green).

Setup (Windows)

    Requirements:
        CMake (minimum version 3.5)
        FreeRTOS
        MinGW or Visual Studio (for MSVC compiler)

    Building:
        Clone the repository and navigate to the project directory.
        Create a build directory: mkdir build && cd build
        Generate build files for MinGW: cmake -G "MinGW Makefiles" .. or for Visual Studio: cmake -G "Visual Studio" ..
        Build the project with MinGW: mingw32-make or with Visual Studio: open the generated solution file and build it.

    Running:
        After building, an executable will be generated.
        Run the executable from the command line: ./<executable_name>.exe for MinGW or directly from Visual Studio.

Usage

    The system will start simulating trains and cars crossing the intersection.
    Trains and cars will be displayed with their respective IDs and actions (e.g., arrival, crossing).
    The gate status and semaphore lights will be updated accordingly.