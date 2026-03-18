cmake_minimum_required(VERSION 3.28)
project(AsusROGSpathaX_driver)

set(timer_lib src/timer.cpp)

add_library(utils_timer STATIC ${timer_lib})
add_library(utils::timer ALIAS utils_timer)

target_link_libraries(utils_timer include_dir)
target_link_libraries(utils_timer libusb::libusb)