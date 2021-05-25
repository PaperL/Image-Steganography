cmake_minimum_required(VERSION 3.16)
project(Image_Steganography)
set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fconcepts")
include_directories(
        ${PROJECT_SOURCE_DIR}/src/
)
set(src_dir
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        )
add_executable(code ${src_dir})