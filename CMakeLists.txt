cmake_minimum_required(VERSION 3.25.0)
project(3DRenderer VERSION 0.1.0 LANGUAGES C)
#set(CMAKE_C_STANDARD 98)
#set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow)
endif()
# Find SDL2
find_package(SDL2 REQUIRED)
# Add the executable target
add_executable(3DRenderer src/main.c src/mesh.c)

# Include SDL2 headers
target_include_directories(3DRenderer PRIVATE ${SDL2_INCLUDE_DIRS})

# Link SDL2 library
target_link_libraries(3DRenderer PRIVATE ${SDL2_LIBRARIES})
