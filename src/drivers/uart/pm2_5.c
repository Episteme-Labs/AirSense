/**
 * File: pm2_5.c
 * Author: trung.la
 * Date: November 06 2025
 * Description: Implementation file for PMS7003 PM2.5 sensor driver with HAL injection
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 */

#include "pm2_5.h"
#include "pm2_5_hal.h"
#include "pin_config.h"
#include "pms7003_defs.h"
#include <stdio.h>

// Static HAL instance - set during init
static const pm25_hal_t *g_hal = NULL;

void pm25_sensor_init(const pm25_hal_t *hal) {
    // Use provided HAL or default to real hardware
    g_hal = (hal != NULL) ? hal : pm25_get_default_hal();
    
    // Initialize UART with the configured baud rate
    g_hal->uart->init(PMS_UART, PMS_BAUD_RATE);
    
    // Configure TX and RX pins for UART
    g_hal->gpio->set_function(PMS_TX_PIN, GPIO_FUNC_UART);
    g_hal->gpio->set_function(PMS_RX_PIN, GPIO_FUNC_UART);
    
    // Initialize SET pin (for mode control)
    g_hal->gpio->init(PMS_SET_PIN);
    g_hal->gpio->set_dir(PMS_SET_PIN, true);  // Output
    g_hal->gpio->put(PMS_SET_PIN, 1);         // Active mode
    
    // Initialize RESET pin
    g_hal->gpio->init(PMS_RESET_PIN);
    g_hal->gpio->set_dir(PMS_RESET_PIN, true);  // Output
    g_hal->gpio->put(PMS_RESET_PIN, 1);         // Not in reset
    
    // Send passive mode command
    uint8_t passive_mode_cmd[7] = {0x42, 0x4D, 0xE1, 0x00, 0x00, 0x01, 0x70};
    g_hal->uart->write_blocking(PMS_UART, passive_mode_cmd, 7);
}

bool pm25_sensor_read(pm25_data_t *data) {
    if (data == NULL || g_hal == NULL) {
        printf("DEBUG: data=%p, g_hal=%p\n", (void*)data, (void*)g_hal);
        return false;
    }
    
    uint8_t frame[PMS_FRAME_LENGTH];
    
    // Check if data is available
    if (!g_hal->uart->is_readable(PMS_UART)) {
        printf("DEBUG: UART not readable\n");
        return false;
    }
    
    // Read start bytes
    g_hal->uart->read_blocking(PMS_UART, &frame[0], 1);
    printf("DEBUG: Start1: 0x%02X\n", frame[0]);
    if (frame[0] != PMS_FRAME_START1) {
        return false;
    }
    
    g_hal->uart->read_blocking(PMS_UART, &frame[1], 1);
    printf("DEBUG: Start2: 0x%02X\n", frame[1]);
    if (frame[1] != PMS_FRAME_START2) {
        return false;
    }
    
    // Read the rest of the frame
    g_hal->uart->read_blocking(PMS_UART, &frame[2], PMS_FRAME_LENGTH - 2);
    
    // Verify frame length
    uint16_t frame_len = (frame[2] << 8) | frame[3];
    printf("DEBUG: Frame len: %u\n", frame_len);
    if (frame_len != PMS_DATA_FRAME_LEN) {
        return false;
    }
    
    // Calculate and verify checksum
    uint16_t checksum = 0;
    for (int i = 0; i < PMS_FRAME_LENGTH - 2; i++) {
        checksum += frame[i];
    }
    uint16_t received_checksum = (frame[PMS_FRAME_LENGTH - 2] << 8) | frame[PMS_FRAME_LENGTH - 1];
    
    printf("DEBUG: Checksum calc=0x%04X recv=0x%04X\n", checksum, received_checksum);
    if (checksum != received_checksum) {
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
    
    printf("DEBUG: Parse OK, pm1_0=%u\n", data->pm1_0_cf1);
    return true;
}