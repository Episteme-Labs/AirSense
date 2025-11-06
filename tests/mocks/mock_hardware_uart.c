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

// Mock state
static bool mock_uart_is_readable_return = false;
static bool mock_ignore_buffer = false;
static uint8_t *mock_read_data = NULL;
static size_t mock_read_data_offset = 0;

void uart_init(uart_inst_t *uart, uint baudrate) {
    // Mock implementation - just verify it was called if needed
}

bool uart_is_readable(uart_inst_t *uart) {
    return mock_uart_is_readable_return;
}

void uart_read_blocking(uart_inst_t *uart, uint8_t *dst, size_t len) {
    if (mock_read_data != NULL && dst != NULL) {
        // Copy mock data to destination
        memcpy(dst, mock_read_data + mock_read_data_offset, len);
        mock_read_data_offset += len;
    }
}

void uart_write_blocking(uart_inst_t *uart, const uint8_t *src, size_t len) {
    // Mock implementation - just verify it was called if needed
}

// Mock control functions

void uart_init_Expect(uart_inst_t *uart, uint baudrate) {
    // Store expectation - for now just note it was called
}

bool uart_is_readable_IgnoreAndReturn(bool value) {
    mock_uart_is_readable_return = value;
    return value;
}

void uart_read_blocking_Expect(uart_inst_t *uart, uint8_t *dst, size_t len) {
    // Store expectation - the actual call will use the mock data
}

void uart_read_blocking_IgnoreArg_buffer(void) {
    mock_ignore_buffer = true;
}

void uart_write_blocking_Expect(uart_inst_t *uart, const uint8_t *src, size_t len) {
    // Store expectation
}

void uart_write_blocking_IgnoreArg_buffer(void) {
    mock_ignore_buffer = true;
}

// Helper function to inject test data
void uart_read_blocking_SetDataToReturn(uint8_t *data) {
    mock_read_data = data;
    mock_read_data_offset = 0;
}

// Reset mock state (call in setUp)
void uart_mock_reset(void) {
    mock_uart_is_readable_return = false;
    mock_ignore_buffer = false;
    mock_read_data = NULL;
    mock_read_data_offset = 0;
}