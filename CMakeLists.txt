cmake_minimum_required(VERSION 3.25.0)
project(3DRenderer VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(UtilityDS REQUIRED)
# Add the executable target
add_executable(3DRenderer 
    src/main.c 
    src/mesh.c
    src/display.c 
    src/exercises.c 
    src/globals.c
    src/vector.c 
    src/triangle.c 
    src/gui.c
    src/parser.c)

# Include SDL2 headers
target_include_directories(3DRenderer PRIVATE ${SDL2_INCLUDE_DIRS}
                            ${CMAKE_CURRENT_SOURCE_DIR}/External)

# Link SDL2 library
target_link_libraries(3DRenderer PRIVATE ${SDL2_LIBRARIES} UtilityDS::UtilityDS)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(3DRenderer PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        #debug
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Debug>:-g3>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
        #release
        $<$<CONFIG:Release>:-O2>
    )
endif()