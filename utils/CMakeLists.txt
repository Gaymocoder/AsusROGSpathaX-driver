cmake_minimum_required(VERSION 3.28)
project(AsusROGSpathaX_driver)

set(exstd_lib src/std.cpp)
set(libusb_lib src/libusb.cpp)
set(logger_lib src/logger.cpp)

add_library(utils_exstd STATIC ${exstd_lib})
add_library(utils_libusb STATIC ${libusb_lib})
add_library(utils_logger STATIC ${logger_lib})

add_library(utils::exstd ALIAS utils_exstd)
add_library(utils::libusb ALIAS utils_libusb)
add_library(utils::logger ALIAS utils_logger)

target_link_libraries(utils_exstd PRIVATE include_dir)
target_link_libraries(utils_exstd PRIVATE utils::logger)
target_link_libraries(utils_exstd PRIVATE spdlog::spdlog)

target_link_libraries(utils_libusb PRIVATE include_dir)
target_link_libraries(utils_libusb PRIVATE utils::exstd)
target_link_libraries(utils_libusb PRIVATE utils::logger)
target_link_libraries(utils_libusb PRIVATE spdlog::spdlog)
target_link_libraries(utils_libusb PRIVATE libusb::libusb)

target_link_libraries(utils_logger PRIVATE include_dir)
target_link_libraries(utils_logger PRIVATE spdlog::spdlog)