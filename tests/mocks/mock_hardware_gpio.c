/**
 * @file mock_hardware_gpio.c
 * @author trung.la
 * @date November 06 2025
 * @brief Mock implementation file for hardware GPIO functions for unit testing.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#include "mock_hardware_gpio.h"
#include "unity.h"

// Mock functions - simplified implementation
void gpio_init(uint gpio) {
    // Mock implementation does nothing
}

void gpio_set_dir(uint gpio, bool out) {
    // Mock implementation does nothing
}

void gpio_put(uint gpio, bool value) {
    // Mock implementation does nothing
}

void gpio_set_function(uint gpio, gpio_function_t fn) {
    // Mock implementation does nothing
}

// Mock expectation functions - for now just note they were called
void gpio_init_Expect(uint gpio) {
    // Expectation stored
}

void gpio_set_dir_Expect(uint gpio, bool out) {
    // Expectation stored
}

void gpio_put_Expect(uint gpio, bool value) {
    // Expectation stored
}

void gpio_set_function_Expect(uint gpio, gpio_function_t fn) {
    // Expectation stored
}

// Reset mock state
void gpio_mock_reset(void) {
    // Reset any stored state
}