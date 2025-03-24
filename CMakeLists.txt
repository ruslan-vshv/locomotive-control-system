cmake_minimum_required(VERSION 3.30)
project(locomotive_control_system C)

set(CMAKE_C_STANDARD 11)

# Define source files
set(SOURCES
        main.c
        core/translator.c
        core/logger.c
        core/user_interface.c
        core/autoloader.c
        modules/brake.c
        core/modules_menu.c
)

# Define header files (for IDEs, not strictly required for build)
set(HEADERS
        core/translator.h
        core/logger.h
        core/user_interface.h
        core/autoloader.h
        modules/brake.h
        core/module.h
        core/modules_menu.h
)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
