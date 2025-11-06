/**
 * @file mock_hardware_uart.h
 * @author trung.la
 * @date November 06 2025
 * @brief Mock header file for hardware UART functions for unit testing.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#ifndef MOCK_HARDWARE_UART_H
#define MOCK_HARDWARE_UART_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// Type definitions needed for UART mocking
typedef unsigned int uint;
typedef struct uart_inst uart_inst_t;

// Mock function declarations
void uart_init(uart_inst_t *uart, uint baudrate);
bool uart_is_readable(uart_inst_t *uart);
void uart_read_blocking(uart_inst_t *uart, uint8_t *dst, size_t len);
void uart_write_blocking(uart_inst_t *uart, const uint8_t *src, size_t len);

void uart_init_Expect(uart_inst_t *uart, uint baudrate);
bool uart_is_readable_IgnoreAndReturn(bool value);
void uart_read_blocking_Expect(uart_inst_t *uart, uint8_t *dst, size_t len);
void uart_read_blocking_IgnoreArg_buffer(void);
void uart_write_blocking_Expect(uart_inst_t *uart, const uint8_t *src, size_t len);
void uart_write_blocking_IgnoreArg_buffer(void);

// Mock control helpers
void uart_read_blocking_SetDataToReturn(uint8_t *data);
void uart_mock_reset(void);

#endif // MOCK_HARDWARE_UART_H