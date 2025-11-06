/**
 * @file pm2_5_hal_mock.c
 * @author trung.la
 * @date November 06 2025
 * @brief Mock HAL implementation for PM2.5 sensor testing
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 */

#include "pm2_5_hal.h"
#include "mock_hardware_uart.h"
#include "mock_hardware_gpio.h"

// Mock HAL wraps our existing mock functions
static const pm25_uart_hal_t mock_uart_hal = {
    .init = uart_init,
    .is_readable = uart_is_readable,
    .read_blocking = uart_read_blocking,
    .write_blocking = uart_write_blocking
};

static const pm25_gpio_hal_t mock_gpio_hal = {
    .init = gpio_init,
    .set_dir = gpio_set_dir,
    .put = gpio_put,
    .set_function = gpio_set_function
};

static const pm25_hal_t mock_hal = {
    .uart = &mock_uart_hal,
    .gpio = &mock_gpio_hal
};

const pm25_hal_t* pm25_get_mock_hal(void) {
    return &mock_hal;
}

// For test builds, default HAL is the mock
const pm25_hal_t* pm25_get_default_hal(void) {
    return &mock_hal;
}
