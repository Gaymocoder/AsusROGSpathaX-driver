cmake_minimum_required(VERSION 3.28)
project(AsusROGSpathaX_driver)

set(exstd_lib src/std.cpp)
set(timer_lib src/timer.cpp)
set(libusb_lib src/libusb.cpp)

add_library(utils_exstd STATIC ${exstd_lib})
add_library(utils_timer STATIC ${timer_lib})
add_library(utils_libusb STATIC ${libusb_lib})

add_library(utils::exstd ALIAS utils_exstd)
add_library(utils::timer ALIAS utils_timer)
add_library(utils::libusb ALIAS utils_libusb)

target_link_libraries(utils_exstd PRIVATE include_dir)
target_link_libraries(utils_exstd PRIVATE spdlog::spdlog)

target_link_libraries(utils_timer PRIVATE include_dir)
target_link_libraries(utils_libusb PRIVATE include_dir)
target_link_libraries(utils_libusb PRIVATE utils::exstd)
target_link_libraries(utils_libusb PRIVATE libusb::libusb)