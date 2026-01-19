cmake_minimum_required(VERSION 4.1)
project(CaveRun)

set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(include)

# Source files
set(SOURCES
        src/Character.cpp
        src/Player.cpp
        src/Monster.cpp
        src/Room.cpp
        src/PoisonRoom.cpp
        src/TrapRoom.cpp
        src/Map.cpp
        src/Game.cpp
        main.cpp


)

# Header files (for IDE visibility)
set(HEADERS
        include/Character.h
        include/Player.h
        include/Monster.h
        include/Room.h
        include/PoisonRoom.h
        include/TrapRoom.h
        include/Map.h
        include/Game.h
        include/Monster.h



)

# Create executable
add_executable(CaveRun ${SOURCES} ${HEADERS})

# Compiler warnings
if (MSVC)
    target_compile_options(CaveRun PRIVATE /W4)
else ()
    target_compile_options(CaveRun PRIVATE -Wall -Wextra -Wpedantic)
endif ()

# Enable debugging symbols
set(CMAKE_BUILD_TYPE Debug)