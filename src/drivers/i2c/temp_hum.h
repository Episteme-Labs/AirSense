/**
 * File: temp_hum.h
 * Author: trung.la
 * Date: November 06 2025
 * Description: Header file for temperature and humidity sensor driver, defining data structures and function prototypes for I2C-based interaction on Raspberry Pi Pico.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs Company. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#ifndef TEMP_HUM_H
#define TEMP_HUM_H

#include <stdbool.h>

// Function prototypes
bool init_temp_hum_sensor();
bool read_temp_hum_data(float *temperature, float *humidity);

#endif // TEMP_HUM_H
