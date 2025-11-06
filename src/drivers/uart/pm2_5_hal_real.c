/**
 * @file pm2_5_hal_real.c
 * @author trung.la
 * @date November 06 2025
 * @brief Real hardware implementation of PM2.5 HAL using Pico SDK
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 */

#include "pm2_5_hal.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"

// Real UART implementation using Pico SDK
static void real_uart_init(uart_inst_t *uart, uint baudrate) {
    uart_init(uart, baudrate);
}

static bool real_uart_is_readable(uart_inst_t *uart) {
    return uart_is_readable(uart);
}

static void real_uart_read_blocking(uart_inst_t *uart, uint8_t *dst, size_t len) {
    uart_read_blocking(uart, dst, len);
}

static void real_uart_write_blocking(uart_inst_t *uart, const uint8_t *src, size_t len) {
    uart_write_blocking(uart, src, len);
}

// Real GPIO implementation using Pico SDK
static void real_gpio_init(uint gpio) {
    gpio_init(gpio);
}

static void real_gpio_set_dir(uint gpio, bool out) {
    gpio_set_dir(gpio, out);
}

static void real_gpio_put(uint gpio, bool value) {
    gpio_put(gpio, value);
}

static void real_gpio_set_function(uint gpio, gpio_function_t fn) {
    gpio_set_function(gpio, fn);
}

// HAL instances
static const pm25_uart_hal_t real_uart_hal = {
    .init = real_uart_init,
    .is_readable = real_uart_is_readable,
    .read_blocking = real_uart_read_blocking,
    .write_blocking = real_uart_write_blocking
};

static const pm25_gpio_hal_t real_gpio_hal = {
    .init = real_gpio_init,
    .set_dir = real_gpio_set_dir,
    .put = real_gpio_put,
    .set_function = real_gpio_set_function
};

static const pm25_hal_t real_hal = {
    .uart = &real_uart_hal,
    .gpio = &real_gpio_hal
};

const pm25_hal_t* pm25_get_default_hal(void) {
    return &real_hal;
}
