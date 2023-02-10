cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pwm_read C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()


add_executable(pwm_read
    rc_receiver.cpp
    ReadReceiver.cpp
)

pico_generate_pio_header(pwm_read ${CMAKE_CURRENT_LIST_DIR}/ReadReceiver.pio)

target_link_libraries(pwm_read
    pico_stdlib
    hardware_pio
    hardware_pwm
    hardware_gpio
)


SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

pico_enable_stdio_usb(pwm_read 1)
pico_enable_stdio_uart(pwm_read 0)

pico_add_extra_outputs(pwm_read)
