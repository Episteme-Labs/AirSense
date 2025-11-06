/**
 * @file mock_hardware_gpio.h
 * @author trung.la
 * @date November 06 2025
 * @brief Mock header file for hardware GPIO functions for unit testing.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#ifndef MOCK_HARDWARE_GPIO_H
#define MOCK_HARDWARE_GPIO_H

#include <stdint.h>
#include <stdbool.h>

// Include HAL header for type consistency
#include "pm2_5_hal.h"

// Type definitions needed for GPIO mocking (uint comes from HAL)
// gpio_function_t comes from HAL

// Mock function declarations
void gpio_init(uint gpio);
void gpio_set_dir(uint gpio, bool out);
void gpio_put(uint gpio, bool value);
void gpio_set_function(uint gpio, gpio_function_t fn);

// Mock controls
void gpio_init_Expect(uint gpio);
void gpio_set_dir_Expect(uint gpio, bool out);
void gpio_put_Expect(uint gpio, bool value);
void gpio_set_function_Expect(uint gpio, gpio_function_t fn);

// Mock control helpers
void gpio_mock_reset(void);

#endif // MOCK_HARDWARE_GPIO_H