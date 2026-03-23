cmake_minimum_required(VERSION 3.28)
project(AsusROGSpathaX_driver)

set(MAIN_EXE src/main.cpp)

add_executable(SpathaX_driver ${MAIN_EXE})
set_target_properties(SpathaX_driver PROPERTIES OUTPUT_NAME "SpathaX (driver)")

target_link_libraries(SpathaX_driver PRIVATE utils::exstd)
target_link_libraries(SpathaX_driver PRIVATE utils::libusb)
target_link_libraries(SpathaX_driver PRIVATE utils::logger)