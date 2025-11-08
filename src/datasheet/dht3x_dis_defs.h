/**
 * File: dht3x_dis_defs.h
 * Author: trung.la
 * Date: November 06 2025
 * Description: Definitions and data structures for DHT3X temperature and humidity sensor driver, used in I2C communication on Raspberry Pi Pico.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs Company. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#ifndef SHT3X_DIS_DEFS_H
#define SHT3X_DIS_DEFS_H

#include <stdint.h>

// I2C Addresses
#define SHT3X_ADDR_A            0x44  // Default, ADDR pin low
#define SHT3X_ADDR_B            0x45  // ADDR pin high

// Command lengths (all commands are 2 bytes)
#define SHT3X_CMD_LEN           2

// Single Shot Measurement Commands (with clock stretching)
const uint8_t SHT3X_CMD_SINGLE_HIGH_STRETCH[SHT3X_CMD_LEN]   = {0x2C, 0x06};
const uint8_t SHT3X_CMD_SINGLE_MED_STRETCH[SHT3X_CMD_LEN]    = {0x2C, 0x0D};
const uint8_t SHT3X_CMD_SINGLE_LOW_STRETCH[SHT3X_CMD_LEN]    = {0x2C, 0x10};

// Single Shot Measurement Commands (no clock stretching)
const uint8_t SHT3X_CMD_SINGLE_HIGH[SHT3X_CMD_LEN]           = {0x24, 0x00};
const uint8_t SHT3X_CMD_SINGLE_MED[SHT3X_CMD_LEN]            = {0x24, 0x0B};
const uint8_t SHT3X_CMD_SINGLE_LOW[SHT3X_CMD_LEN]            = {0x24, 0x16};

// Periodic Measurement Commands
// 0.5 measurements per second (mps)
const uint8_t SHT3X_CMD_PERIODIC_0_5_HIGH[SHT3X_CMD_LEN]     = {0x20, 0x32};
const uint8_t SHT3X_CMD_PERIODIC_0_5_MED[SHT3X_CMD_LEN]      = {0x20, 0x24};
const uint8_t SHT3X_CMD_PERIODIC_0_5_LOW[SHT3X_CMD_LEN]      = {0x20, 0x2F};

// 1 mps
const uint8_t SHT3X_CMD_PERIODIC_1_HIGH[SHT3X_CMD_LEN]       = {0x21, 0x30};
const uint8_t SHT3X_CMD_PERIODIC_1_MED[SHT3X_CMD_LEN]        = {0x21, 0x26};
const uint8_t SHT3X_CMD_PERIODIC_1_LOW[SHT3X_CMD_LEN]        = {0x21, 0x2D};

// 2 mps
const uint8_t SHT3X_CMD_PERIODIC_2_HIGH[SHT3X_CMD_LEN]       = {0x22, 0x36};
const uint8_t SHT3X_CMD_PERIODIC_2_MED[SHT3X_CMD_LEN]        = {0x22, 0x20};
const uint8_t SHT3X_CMD_PERIODIC_2_LOW[SHT3X_CMD_LEN]        = {0x22, 0x2B};

// 4 mps
const uint8_t SHT3X_CMD_PERIODIC_4_HIGH[SHT3X_CMD_LEN]       = {0x23, 0x34};
const uint8_t SHT3X_CMD_PERIODIC_4_MED[SHT3X_CMD_LEN]        = {0x23, 0x22};
const uint8_t SHT3X_CMD_PERIODIC_4_LOW[SHT3X_CMD_LEN]        = {0x23, 0x29};

// 10 mps
const uint8_t SHT3X_CMD_PERIODIC_10_HIGH[SHT3X_CMD_LEN]      = {0x27, 0x37};
const uint8_t SHT3X_CMD_PERIODIC_10_MED[SHT3X_CMD_LEN]       = {0x27, 0x21};
const uint8_t SHT3X_CMD_PERIODIC_10_LOW[SHT3X_CMD_LEN]       = {0x27, 0x2A};

// Other Commands
const uint8_t SHT3X_CMD_FETCH_DATA[SHT3X_CMD_LEN]            = {0xE0, 0x00};  // For periodic mode
const uint8_t SHT3X_CMD_ART[SHT3X_CMD_LEN]                   = {0x2B, 0x32};  // Accelerated Response Time
const uint8_t SHT3X_CMD_BREAK[SHT3X_CMD_LEN]                 = {0x30, 0x93};  // Stop periodic mode
const uint8_t SHT3X_CMD_SOFT_RESET[SHT3X_CMD_LEN]            = {0x30, 0xA2};
const uint8_t SHT3X_CMD_HEATER_ENABLE[SHT3X_CMD_LEN]         = {0x30, 0x6D};
const uint8_t SHT3X_CMD_HEATER_DISABLE[SHT3X_CMD_LEN]        = {0x30, 0x66};
const uint8_t SHT3X_CMD_READ_STATUS[SHT3X_CMD_LEN]           = {0xF3, 0x2D};
const uint8_t SHT3X_CMD_CLEAR_STATUS[SHT3X_CMD_LEN]          = {0x30, 0x41};

// Status Register Bit Masks
#define SHT3X_STATUS_ALERT_PENDING      (1 << 15)
#define SHT3X_STATUS_HEATER_ON          (1 << 13)
#define SHT3X_STATUS_RH_ALERT           (1 << 11)
#define SHT3X_STATUS_T_ALERT            (1 << 10)
#define SHT3X_STATUS_SYSTEM_RESET       (1 << 4)
#define SHT3X_STATUS_CMD_STATUS         (1 << 1)
#define SHT3X_STATUS_WRITE_CRC_FAIL     (1 << 0)

// CRC Calculation Properties (for 8-bit CRC)
#define SHT3X_CRC_POLYNOMIAL            0x31  // x^8 + x^5 + x^4 + 1
#define SHT3X_CRC_INIT                  0xFF

#endif // SHT3X_DIS_DEFS_H
