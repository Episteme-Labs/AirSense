/**
 * @file test_pm2_5.c
 * @author trung.la
 * @date November 06 2025
 * @brief Test-specific implementation of PM2.5 sensor driver for unit testing.
 * This version uses mocks instead of real hardware.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 */

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

void pm25_sensor_init(void) {
    // Initialize UART with the configured baud rate
    uart_init(PMS_UART, PMS_BAUD_RATE);
    
    // Configure TX and RX pins for UART
    gpio_set_function(PMS_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(PMS_RX_PIN, GPIO_FUNC_UART);
    
    // Initialize SET pin (for mode control)
    gpio_init(PMS_SET_PIN);
    gpio_set_dir(PMS_SET_PIN, true);  // Output
    gpio_put(PMS_SET_PIN, 1);         // Active mode
    
    // Initialize RESET pin
    gpio_init(PMS_RESET_PIN);
    gpio_set_dir(PMS_RESET_PIN, true);  // Output
    gpio_put(PMS_RESET_PIN, 1);         // Not in reset
    
    // Send passive mode command (placeholder - actual command would be sent here)
    uint8_t passive_mode_cmd[7] = {0x42, 0x4D, 0xE1, 0x00, 0x00, 0x01, 0x70};
    uart_write_blocking(PMS_UART, passive_mode_cmd, 7);
}

bool pm25_sensor_read(pm25_data_t *data) {
    if (data == NULL) {
        return false;
    }
    
    uint8_t frame[PMS_FRAME_LENGTH];
    
    // Check if data is available
    if (!uart_is_readable(PMS_UART)) {
        printf("DEBUG: uart_is_readable returned false\n");
        return false;
    }
    
    // Read start bytes
    uart_read_blocking(PMS_UART, &frame[0], 1);
    printf("DEBUG: frame[0] = 0x%02X (expected 0x%02X)\n", frame[0], PMS_FRAME_START1);
    if (frame[0] != PMS_FRAME_START1) {
        printf("DEBUG: Bad start byte 1\n");
        return false;
    }
    
    uart_read_blocking(PMS_UART, &frame[1], 1);
    printf("DEBUG: frame[1] = 0x%02X (expected 0x%02X)\n", frame[1], PMS_FRAME_START2);
    if (frame[1] != PMS_FRAME_START2) {
        printf("DEBUG: Bad start byte 2\n");
        return false;
    }
    
    // Read the rest of the frame
    uart_read_blocking(PMS_UART, &frame[2], PMS_FRAME_LENGTH - 2);
    
    // Verify frame length
    uint16_t frame_len = (frame[2] << 8) | frame[3];
    printf("DEBUG: frame_len = %d (expected %d)\n", frame_len, PMS_DATA_FRAME_LEN);
    if (frame_len != PMS_DATA_FRAME_LEN) {
        printf("DEBUG: Bad frame length\n");
        return false;
    }
    
    // Calculate and verify checksum
    uint16_t checksum = 0;
    for (int i = 0; i < PMS_FRAME_LENGTH - 2; i++) {
        checksum += frame[i];
    }
    uint16_t received_checksum = (frame[PMS_FRAME_LENGTH - 2] << 8) | frame[PMS_FRAME_LENGTH - 1];
    
    printf("DEBUG: Frame bytes 28-31: 0x%02X 0x%02X 0x%02X 0x%02X\n", 
           frame[28], frame[29], frame[30], frame[31]);
    printf("DEBUG: calculated checksum = 0x%04X, received = 0x%04X\n", checksum, received_checksum);
    if (checksum != received_checksum) {
        printf("DEBUG: Checksum mismatch\n");
        return false;
    }
    
    // Parse the data
    data->pm1_0_cf1 = (frame[4] << 8) | frame[5];
    data->pm2_5_cf1 = (frame[6] << 8) | frame[7];
    data->pm10_cf1 = (frame[8] << 8) | frame[9];
    data->pm1_0_atm = (frame[10] << 8) | frame[11];
    data->pm2_5_atm = (frame[12] << 8) | frame[13];
    data->pm10_atm = (frame[14] << 8) | frame[15];
    data->count_0_3 = (frame[16] << 8) | frame[17];
    data->count_0_5 = (frame[18] << 8) | frame[19];
    data->count_1_0 = (frame[20] << 8) | frame[21];
    data->count_2_5 = (frame[22] << 8) | frame[23];
    data->count_5_0 = (frame[24] << 8) | frame[25];
    data->count_10 = (frame[26] << 8) | frame[27];
    
    return true;
}
