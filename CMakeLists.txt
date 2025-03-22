cmake_minimum_required(VERSION 3.30)
project(locomotive_control_system C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mconsole")

# Define source files
set(SOURCES
        main.c
        core/translator.c
)

# Define header files (for IDEs, not strictly required for build)
set(HEADERS
        core/translator.h
)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
