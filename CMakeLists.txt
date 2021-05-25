cmake_minimum_required(VERSION 3.16)
project(Image_Steganography)
set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fconcepts")
include_directories(
        ${PROJECT_SOURCE_DIR}/third/
)
set(src_dir
        ${PROJECT_SOURCE_DIR}/third/LBitmap1.cpp
        )
# add_executable(trans ${src_dir} src/TransImage.cpp)
# add_executable(encrypt ${src_dir} src/R-LSB_encrypt.cpp)
# add_executable(decrypt ${src_dir} src/R-LSB_decrypt.cpp)

# add_executable(encrypt ${src_dir} src/Experiment1/R-LSB_encrypt.cpp)
add_executable(decrypt ${src_dir} src/Experiment1/R-LSB_decrypt.cpp)