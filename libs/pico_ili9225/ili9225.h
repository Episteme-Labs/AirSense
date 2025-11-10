/**
 * File: ili9225.h
 * Author: trung.la
 * Date: November 10 2025
 * Description: Header file for ILI9225 LCD driver for Raspberry Pi Pico
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs Company. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#ifndef ILI9225_H
#define ILI9225_H

#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"

// Structure to hold ILI9225 configuration
typedef struct {
    spi_inst_t* spi_inst; // SPI instance (e.g., spi0 or spi1)
    uint pin_sck;   // SPI clock pin
    uint pin_mosi;  // SPI MOSI pin
    uint pin_miso; // SPI MISO pin (if used)
    uint pin_cs;    // Chip select pin
    uint pin_dc;    // Data/Command control pin
    uint pin_reset; // Reset pin

    uint16_t width;    // Display width in pixels
    uint16_t height;   // Display height in pixels
} ili9225_config_t;

// Screen Rotation
typedef enum {
    ILI9225_ROTATION_0,
    ILI9225_ROTATION_90,
    ILI9225_ROTATION_180,
    ILI9225_ROTATION_270
} ili9225_rotation_t;

// Public API

/**
 * @brief Initialize the ILI9225 LCD display with the given configuration
 * 
 * @param config Pointer to ili9225_config_t structure with initialization parameters
 * @return void
 */
void ili9225_init(const ili9225_config_t* config);

#endif // ILI9225_H
