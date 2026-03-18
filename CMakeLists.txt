cmake_minimum_required(VERSION 3.28)
project(AsusROGSpathaX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(libusb REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_compile_options(-Wall -Wextra -pedantic)

add_library(include_dir INTERFACE)
target_include_directories(include_dir INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(utils)
add_subdirectory(driver)