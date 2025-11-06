/**
 * File: pm2_5.cpp
 * Author: trung.la
 * Date: November 06 2025
 * Description: Implementation file for PMS7003 PM2.5 sensor driver, defining data structures and function prototypes for UART-based interaction on Raspberry Pi Pico.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#include "pm2_5.h"

#include "hardware/uart.h"
#include "hardware/gpio.h"

void pm25_sensor_init(void) {
}

bool pm25_sensor_read(pm25_data_t *data) {
    return true;
}