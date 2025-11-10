add_library(pico_ili9225
STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ili9225_defs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ili9225.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ili9225.h
)

target_include_directories(pico_ili9225 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(pico_ili9225 PRIVATE
    pico_stdlib
    hardware_spi
    hardware_gpio
)