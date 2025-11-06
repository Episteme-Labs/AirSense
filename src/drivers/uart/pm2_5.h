/**
 * File: pm2_5.h
 * Author: trung.la
 * Date: November 06 2025
 * Description: Header file for PMS7003 PM2.5 sensor driver, defining data structures and function prototypes for UART-based interaction on Raspberry Pi Pico.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs Company. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#ifndef PM25_SENSOR_H
#define PM25_SENSOR_H

#include <stdint.h>
#include <stdbool.h>

// Structure to hold PM2.5 sensor data based on PMS7003 output format
typedef struct {
    uint16_t pm1_0_cf1;     // PM1.0 concentration (CF=1, standard particle) in μg/m³
    uint16_t pm2_5_cf1;     // PM2.5 concentration (CF=1, standard particle) in μg/m³
    uint16_t pm10_cf1;      // PM10 concentration (CF=1, standard particle) in μg/m³
    uint16_t pm1_0_atm;     // PM1.0 concentration (atmospheric environment) in μg/m³
    uint16_t pm2_5_atm;     // PM2.5 concentration (atmospheric environment) in μg/m³
    uint16_t pm10_atm;      // PM10 concentration (atmospheric environment) in μg/m³
    uint16_t count_0_3;     // Number of particles >0.3μm in 0.1L air
    uint16_t count_0_5;     // Number of particles >0.5μm in 0.1L air
    uint16_t count_1_0;     // Number of particles >1.0μm in 0.1L air
    uint16_t count_2_5;     // Number of particles >2.5μm in 0.1L air
    uint16_t count_5_0;     // Number of particles >5.0μm in 0.1L air
    uint16_t count_10;      // Number of particles >10μm in 0.1L air
} pm25_data_t;

// Initialize the pm2.5 sensor (PMS7003 via UART)
void pm25_sensor_init(void);

// Read data from PM2.5 sensor
// Return true on successful read with valid checksum, false otherwise
bool pm25_sensor_read(pm25_data_t *data);

#endif // PM25_SENSOR_H