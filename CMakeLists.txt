cmake_minimum_required(VERSION 3.15)
project(MyGameProject)

set(CMAKE_CXX_STANDARD 17)

set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/dep/SDL3-3.2.20/x86_64-w64-mingw32")
set(SDL3_INCLUDE_DIR "${SDL3_ROOT}/include")
set(SDL3_LIBRARY "${SDL3_ROOT}/lib/libSDL3.dll.a")

SET(SDL3_IMG_ROOT "${CMAKE_SOURCE_DIR}/dep/SDL3_image-3.2.4/x86_64-w64-mingw32")
SET(SDL3_IMG_INCLUDE_DIR "${SDL3_IMG_ROOT}/include")
set(SDL3_IMG_LIBRARY "${SDL3_IMG_ROOT}/lib/libSDL3_image.dll.a")

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

# Add executable
add_executable(MyGame src/main.cpp
        src/LTexture.cpp
        src/LTexture.h
        src/App.cpp
        src/App.h
        src/GameLoop.cpp
        src/GameLoop.h
        src/utility.h
        src/utility.cpp)

target_include_directories(MyGame PRIVATE ${SDL3_INCLUDE_DIR} ${SDL3_IMG_INCLUDE_DIR})

# Link SDL3
target_link_libraries(MyGame ${SDL3_LIBRARY} ${SDL3_IMG_LIBRARY})
