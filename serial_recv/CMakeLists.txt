cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(serial_recv C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()


add_executable(serial_recv
    serial_recv.cpp
)

target_link_libraries(serial_recv
    pico_stdlib
)


SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

pico_enable_stdio_usb(serial_recv 1)
pico_enable_stdio_uart(serial_recv 0)

pico_add_extra_outputs(serial_recv)

