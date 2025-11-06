/**
 * @file pm2_5_hal.h
 * @author trung.la
 * @date November 06 2025
 * @brief Hardware Abstraction Layer for PM2.5 sensor driver
 * 
 * This HAL allows the driver to work with either real hardware or mocks,
 * making the code testable without hardware dependencies.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 */

#ifndef PM25_HAL_H
#define PM25_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Forward declarations - actual types defined elsewhere
// For real hardware: defined in Pico SDK
// For mocks: defined in mock headers
#ifndef PM25_HAL_MOCK_BUILD
// Building for real hardware - need GPIO types from SDK
#include "hardware/gpio.h"
typedef struct uart_inst uart_inst_t;
typedef unsigned int uint;
#else
// Building for tests - define minimal types
typedef struct uart_inst uart_inst_t;
typedef unsigned int uint;
typedef enum {
    GPIO_FUNC_UART = 2
} gpio_function_t;
#endif

/**
 * @brief UART Hardware Abstraction Layer
 * 
 * Function pointers for UART operations. Can be implemented by real hardware
 * or mock functions for testing.
 */
typedef struct {
    void (*init)(uart_inst_t *uart, uint baudrate);
    bool (*is_readable)(uart_inst_t *uart);
    void (*read_blocking)(uart_inst_t *uart, uint8_t *dst, size_t len);
    void (*write_blocking)(uart_inst_t *uart, const uint8_t *src, size_t len);
} pm25_uart_hal_t;

/**
 * @brief GPIO Hardware Abstraction Layer
 * 
 * Function pointers for GPIO operations. Can be implemented by real hardware
 * or mock functions for testing.
 */
typedef struct {
    void (*init)(uint gpio);
    void (*set_dir)(uint gpio, bool out);
    void (*put)(uint gpio, bool value);
    void (*set_function)(uint gpio, gpio_function_t fn);
} pm25_gpio_hal_t;

/**
 * @brief Complete Hardware Abstraction Layer for PM2.5 driver
 * 
 * Contains both UART and GPIO HALs.
 */
struct pm25_hal {
    const pm25_uart_hal_t *uart;
    const pm25_gpio_hal_t *gpio;
};
typedef struct pm25_hal pm25_hal_t;

// Get the default (real hardware) HAL implementation
const pm25_hal_t* pm25_get_default_hal(void);

#endif // PM25_HAL_H
