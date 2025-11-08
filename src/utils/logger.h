/**
 * File: logger.h
 * Author: trung.la
 * Date: November 08 2025
 * Description: Header file for logging utilities, providing function prototypes for logging messages in the AirSense project.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#ifndef LOGGER_H
#define LOGGER_H

/**
 * Initialize the logging system.
 */
void init_logger();

/**
 * Log a debug message.
 */
void log_debug(const char *message, ...);

#endif // LOGGER_H