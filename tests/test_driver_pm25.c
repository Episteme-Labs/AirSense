/**
 * File: test_driver_pm25.c
 * Author: trung.la
 * Date: November 06 2025
 * Description: Unit tests for PMS7003 PM2.5 sensor driver using CUnit framework
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#include "unity.h"
#include "pm2_5.h"
#include "pms7003_defs.h"
#include "mock_hardware_uart.h"
#include "mock_hardware_gpio.h"

// For testing, define PMS_UART as a mock pointer and pin definitions
#define PMS_UART ((uart_inst_t*)0x1)  // Mock UART instance
#define PMS_TX_PIN 0
#define PMS_RX_PIN 1
#define PMS_SET_PIN 2
#define PMS_RESET_PIN 3
#define GPIO_OUT true

static uint8_t valid_frame[PMS_FRAME_LENGTH] = {
    PMS_FRAME_START1, PMS_FRAME_START2,  // Start bytes
    0x00, PMS_DATA_FRAME_LEN,            // Frame length (28)
    0x00, 0x0A,                          // PM1.0 CF=1: 10
    0x00, 0x19,                          // PM2.5 CF=1: 25
    0x00, 0x32,                          // PM10 CF=1: 50
    0x00, 0x0A,                          // PM1.0 atm: 10
    0x00, 0x19,                          // PM2.5 atm: 25
    0x00, 0x32,                          // PM10 atm: 50
    0x00, 0x64,                          // >0.3μm: 100
    0x00, 0x32,                          // >0.5μm: 50
    0x00, 0x14,                          // >1.0μm: 20
    0x00, 0x0A,                          // >2.5μm: 10
    0x00, 0x05,                          // >5.0μm: 5
    0x00, 0x01,                          // >10μm: 1
    0x00, 0x00,                          // Reserved
    0x01, 0xE1                           // Checksum
};

void setUp(void) {}
void tearDown(void) {}

// Mock UART read for valid frame (simulates response after command)
void mock_uart_read_valid(void) {
    uart_is_readable_IgnoreAndReturn(true);
    uart_read_blocking_Expect(PMS_UART, NULL, 1);
    uart_read_blocking_IgnoreArg_buffer();

    uart_read_blocking_Expect(PMS_UART, NULL, 1);
    uart_read_blocking_IgnoreArg_buffer();

    uart_read_blocking_Expect(PMS_UART, NULL, PMS_FRAME_LENGTH - 2);
    uart_read_blocking_IgnoreArg_buffer();
}

void test_pm25_sensor_read_valid(void) {
    pm25_data_t data;
    mock_uart_read_valid();

    bool result = pm25_sensor_read(&data);

    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_UINT16(10, data.pm1_0_cf1);
    TEST_ASSERT_EQUAL_UINT16(25, data.pm2_5_cf1);
    TEST_ASSERT_EQUAL_UINT16(50, data.pm10_cf1);
    TEST_ASSERT_EQUAL_UINT16(10, data.pm1_0_atm);
    TEST_ASSERT_EQUAL_UINT16(25, data.pm2_5_atm);
    TEST_ASSERT_EQUAL_UINT16(50, data.pm10_atm);
    TEST_ASSERT_EQUAL_UINT16(100, data.count_0_3);
    TEST_ASSERT_EQUAL_UINT16(50, data.count_0_5);
    TEST_ASSERT_EQUAL_UINT16(20, data.count_1_0);
    TEST_ASSERT_EQUAL_UINT16(10, data.count_2_5);
    TEST_ASSERT_EQUAL_UINT16(5, data.count_5_0);
    TEST_ASSERT_EQUAL_UINT16(1, data.count_10);
}

void test_pm25_sensor_read_invalid_checksum(void) {
    pm25_data_t data;
    valid_frame[PMS_FRAME_LENGTH - 2] = 0xFF;  // Corrupt checksum high byte
    mock_uart_read_valid();

    bool result = pm25_sensor_read(&data);

    TEST_ASSERT_FALSE(result);
}

void test_pm25_sensor_read_invalid_frame_length(void) {
    pm25_data_t data;
    valid_frame[3] = 0xFF;  // Corrupt frame length low byte
    mock_uart_read_valid();

    bool result = pm25_sensor_read(&data);

    TEST_ASSERT_FALSE(result);
}

// Additional test for init (mocks GPIO and UART init)
void test_pm25_sensor_init(void) {
    uart_init_Expect(PMS_UART, PMS_BAUD_RATE);

    gpio_set_function_Expect(PMS_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function_Expect(PMS_RX_PIN, GPIO_FUNC_UART);

    gpio_init_Expect(PMS_SET_PIN);
    gpio_set_dir_Expect(PMS_SET_PIN, GPIO_OUT);
    gpio_put_Expect(PMS_SET_PIN, 1);

    gpio_init_Expect(PMS_RESET_PIN);
    gpio_set_dir_Expect(PMS_RESET_PIN, GPIO_OUT);
    gpio_put_Expect(PMS_RESET_PIN, 1);

    uart_write_blocking_Expect(PMS_UART, NULL, 7);  // Expect passive mode command (PMS command is 7 bytes)
    uart_write_blocking_IgnoreArg_buffer();

    pm25_sensor_init();  // Call init and verify mocks
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_pm25_sensor_init);
    RUN_TEST(test_pm25_sensor_read_valid);
    RUN_TEST(test_pm25_sensor_read_invalid_checksum);
    RUN_TEST(test_pm25_sensor_read_invalid_frame_length);
    return UNITY_END();
}