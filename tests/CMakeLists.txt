cmake_minimum_required(VERSION 3.13)

# Build tests for host, not for Pico
project(AirSense_Tests C)

set(CMAKE_C_STANDARD 11)

enable_testing()

set(UNITY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/unity/src)

add_library(unity STATIC ${UNITY_DIR}/unity.c)
target_include_directories(unity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/unity)

# Note: Now using REAL pm2_5.c with mock HAL - no more test doubles!
add_executable(test_driver_pm25
    test_driver_pm25.c
    ../src/drivers/uart/pm2_5.c
    mocks/pm2_5_hal_mock.c
    mocks/mock_hardware_uart.c
    mocks/mock_hardware_gpio.c
)

target_link_libraries(test_driver_pm25
    PRIVATE
    unity
)

target_compile_definitions(test_driver_pm25 PRIVATE 
    PICO_ON_DEVICE=0
    PM25_HAL_MOCK_BUILD=1
)

target_include_directories(test_driver_pm25
    PRIVATE
    ../src/drivers/uart
    ../src/datasheet
    ../src/config
    mocks
    ${UNITY_DIR}
)

add_test(NAME pm25_driver_tests COMMAND test_driver_pm25)