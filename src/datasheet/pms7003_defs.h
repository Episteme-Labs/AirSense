/**
 * File: pms7003_defs.h
 * Author: trung.la
 * Date: November 06 2025
 * Description: Definitions and data structures for PMS7003 PM2.5 sensor driver, used in UART communication on Raspberry Pi Pico.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs Company. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#ifndef PMS7003_DEFS_H
#define PMS7003_DEFS_H

// Technical Specifications (from datasheet Technical Index)
#define PMS_MIN_PARTICLE_DIAM 0.3f      // Minimum distinguishable particle diameter (μm)
#define PMS_RANGE_PM25_STD 0            // Effective Range PM2.5 standard min (μg/m³)
#define PMS_RANGE_PM25_STD_MAX 500      // Effective Range PM2.5 standard max (μg/m³)
#define PMS_MAX_RANGE_PM25_STD 1000     // Maximum Range PM2.5 standard (≥ μg/m³)
#define PMS_RESOLUTION 1                // Resolution (μg/m³)
#define PMS_STD_VOLUME 0.1f             // Standard Volume (L)
#define PMS_SINGLE_RESPONSE_TIME 1      // Single Response Time (< s)
#define PMS_TOTAL_RESPONSE_TIME 10      // Total Response Time (≤ s)
#define PMS_DC_POWER_TYP 5.0f           // DC Power Supply Typical (V)
#define PMS_DC_POWER_MIN 4.5f           // DC Power Supply Min (V)
#define PMS_DC_POWER_MAX 5.5f           // DC Power Supply Max (V)
#define PMS_ACTIVE_CURRENT_MAX 100      // Active Current (≤ mA)
#define PMS_STANDBY_CURRENT_MAX 200     // Standby Current (≤ μA)
#define PMS_INTERFACE_LEVEL_L 0.8f      // Interface Level Low (< @3.3V)
#define PMS_INTERFACE_LEVEL_H 2.7f      // Interface Level High (> @3.3V)
#define PMS_WORK_TEMP_MIN -10          // Working Temperature Range Min (°C)
#define PMS_WORK_TEMP_MAX 60           // Working Temperature Range Max (°C)
#define PMS_WORK_HUM_MIN 0             // Working Humidity Range Min (%)
#define PMS_WORK_HUM_MAX 99            // Working Humidity Range Max (%)
#define PMS_STORAGE_TEMP_MIN -40       // Storage Temperature Range Min (°C)
#define PMS_STORAGE_TEMP_MAX 80        // Storage Temperature Range Max (°C)
#define PMS_MTTF_MIN 3                 // MTTF (≥ Years)
#define PMS_PHYSICAL_SIZE_X 48         // Physical Size X (mm)
#define PMS_PHYSICAL_SIZE_Y 37         // Physical Size Y (mm)
#define PMS_PHYSICAL_SIZE_Z 12         // Physical Size Z (mm)

// Pin Definitions (from datasheet Figure 2: Connector Definition)
#define PMS_PIN1_VCC 1                 // PIN1: VCC (Power 5V)
#define PMS_PIN2_GND 2                 // PIN2: GND (Ground)
#define PMS_PIN3_SET 3                 // PIN3: SET (High/Floating: Normal; Low: Sleep)
#define PMS_PIN4_RXD 4                 // PIN4: RXD (UART Receive, 3.3V TTL)
#define PMS_PIN5_RESET 5               // PIN5: RESET (Low: Reset; High: Normal)
#define PMS_PIN6_NC 6                  // PIN6: NC (No Connect)
#define PMS_PIN7_TXD 7                 // PIN7: TXD (UART Transmit, 3.3V TTL)
#define PMS_PIN8_NC 8                  // PIN8: NC (No Connect)
#define PMS_PIN9_NC 9                  // PIN9: NC (No Connect)
#define PMS_PIN10_NC 10                // PIN10: NC (No Connect)

// UART Communication Parameters (inferred from common PMS series; datasheet implies 9600 baud)
#define PMS_BAUD_RATE 9600             // UART Baud Rate
#define PMS_FRAME_LENGTH 32            // Data Frame Length (bytes)

// Commands (from datasheet or standard PMS protocol; checksum included)
#define PMS_PASSIVE_MODE_CMD_LEN 7
#define PMS_CMD_SET_PASSIVE {0x42, 0x4D, 0xE1, 0x00, 0x00, 0x01, 0x70}  // Set to passive mode
#define PMS_ACTIVE_MODE_CMD_LEN 7
#define PMS_CMD_READ_PASSIVE {0x42, 0x4D, 0xE2, 0x00, 0x00, 0x01, 0x71} // Read data in passive mode
#define PMS_CMD_SET_ACTIVE {0x42, 0x4D, 0xE1, 0x00, 0x01, 0x01, 0x71}   // Set to active mode
#define PMS_CMD_SLEEP {0x42, 0x4D, 0xE4, 0x00, 0x00, 0x01, 0x73}       // Enter sleep mode
#define PMS_CMD_WAKEUP {0x42, 0x4D, 0xE4, 0x00, 0x01, 0x01, 0x74}      // Wake up from sleep

// Data Frame Start Bytes
#define PMS_FRAME_START1 0x42
#define PMS_FRAME_START2 0x4D

// Data Frame Length for Sensor Data (excluding start and checksum)
#define PMS_DATA_FRAME_LEN 28          // Frame length value in bytes 2-3

#endif // PMS7003_DEFS_H
