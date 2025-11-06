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

void gpio_init(uint gpio) {
    // Mock implementation does nothing
}

void gpio_set_dir(uint gpio, bool out) {
    UNITY_TEST_ASSERT_NOT_NULL((void*)gpio, __LINE__, "gpio_set_dir called with NULL gpio");
    // Mock implementation does nothing
}

void gpio_put(uint gpio, bool value) {
    UNITY_TEST_ASSERT_NOT_NULL((void*)gpio, __LINE__, "gpio_put called with NULL gpio");
    // Mock implementation does nothing
}

void gpio_set_function(uint gpio, gpio_function_t fn) {
    UNITY_TEST_ASSERT_NOT_NULL((void*)gpio, __LINE__, "gpio_set_function called with NULL gpio");
    // Mock implementation does nothing
}

void gpio_init_Expect(uint gpio) {
    UNITY_TEST_ASSERT_NOT_NULL((void*)gpio, __LINE__, "gpio_init_Expect called with NULL gpio");
    // Expectation setup can be added here if needed
}

void gpio_set_dir_Expect(uint gpio, bool out) {
    UNITY_TEST_ASSERT_NOT_NULL((void*)gpio, __LINE__, "gpio_set_dir_Expect called with NULL gpio");
    // Expectation setup can be added here if needed
}

void gpio_put_Expect(uint gpio, bool value) {
    UNITY_TEST_ASSERT_NOT_NULL((void*)gpio, __LINE__, "gpio_put_Expect called with NULL gpio");
    // Expectation setup can be added here if needed
}

void gpio_set_function_Expect(uint gpio, gpio_function_t fn) {
    UNITY_TEST_ASSERT_NOT_NULL((void*)gpio, __LINE__, "gpio_set_function_Expect called with NULL gpio");
    // Expectation setup can be added here if needed
}