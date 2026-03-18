cmake_minimum_required(VERSION 3.28)
project(AsusROGSpathaX_driver)

set(timer_lib src/timer.cpp)
set(libusb_lib src/libusb.cpp)

add_library(utils_timer STATIC ${timer_lib})
add_library(utils_libusb STATIC ${libusb_lib})

add_library(utils::timer ALIAS utils_timer)
add_library(utils::libusb ALIAS utils_libusb)

target_link_libraries(utils_timer PRIVATE include_dir)

target_link_libraries(utils_libusb PRIVATE include_dir)
target_link_libraries(utils_libusb PRIVATE libusb::libusb)