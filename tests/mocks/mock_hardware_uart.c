/**
 * @file mock_hardware_uart.c
 * @author trung.la
 * @date November 06 2025
 * @brief Mock implementation file for hardware UART functions for unit testing.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#include "mock_hardware_uart.h"
#include "unity.h"
#include <string.h>

void uart_init(uart_inst_t *uart, uint baudrate) {
    UNITY_TEST_ASSERT_NOT_NULL(uart, __LINE__, "uart_init called with NULL uart");
    // Mock implementation does nothing
}

bool uart_is_readable(uart_inst_t *uart) {
    UNITY_TEST_ASSERT_NOT_NULL(uart, __LINE__, "uart_is_readable called with NULL uart");
    return false; // Default mock behavior
}

void uart_read_blocking(uart_inst_t *uart, uint8_t *dst, size_t len) {
    UNITY_TEST_ASSERT_NOT_NULL(uart, __LINE__, "uart_read_blocking called with NULL uart");
    UNITY_TEST_ASSERT_NOT_NULL(dst, __LINE__, "uart_read_blocking called with NULL dst buffer");
    // Mock implementation does nothing
}

void uart_write_blocking(uart_inst_t *uart, const uint8_t *src, size_t len) {
    UNITY_TEST_ASSERT_NOT_NULL(uart, __LINE__, "uart_write_blocking called with NULL uart");
    UNITY_TEST_ASSERT_NOT_NULL(src, __LINE__, "uart_write_blocking called with NULL src buffer");
    // Mock implementation does nothing
}

void uart_init_Expect(uart_inst_t *uart, uint baudrate) {
    UNITY_TEST_ASSERT_NOT_NULL(uart, __LINE__, "uart_init_Expect called with NULL uart");
    // Expectation setup can be added here if needed
}

bool uart_is_readable_IgnoreAndReturn(bool value) {
    return value;
}

void uart_read_blocking_Expect(uart_inst_t *uart, uint8_t *dst, size_t len) {
    UNITY_TEST_ASSERT_NOT_NULL(uart, __LINE__, "uart_read_blocking_Expect called with NULL uart");
    UNITY_TEST_ASSERT_NOT_NULL(dst, __LINE__, "uart_read_blocking_Expect called with NULL dst buffer");
    // Expectation setup can be added here if needed
}

void uart_read_blocking_IgnoreArg_buffer(void) {
    // This function can be used to ignore the buffer argument in expectations
}

void uart_write_blocking_Expect(uart_inst_t *uart, const uint8_t *src, size_t len) {
    UNITY_TEST_ASSERT_NOT_NULL(uart, __LINE__, "uart_write_blocking_Expect called with NULL uart");
    UNITY_TEST_ASSERT_NOT_NULL(src, __LINE__, "uart_write_blocking_Expect called with NULL src buffer");
    // Expectation setup can be added here if needed
}

void uart_write_blocking_IgnoreArg_buffer(void) {
    // This function can be used to ignore the buffer argument in expectations
}