/**
 * File: logger.c
 * Author: trung.la
 * Date: November 08 2025
 * Description: Implementation file for logging utilities, providing functions for logging messages in the AirSense project
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs Company. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages
 * . All rights reserved in the event of the grant of a patent, utility model or design.
 */

#include "logger.h"

#include <stdio.h>
#include <stdarg.h>

#define LOG_BUFFER_SIZE 256

void init_logger() {
    // TODO: Initialize logging system with UART (e.g., open log file, set log level)
}

void log_debug(const char *message, ...) {
    char buffer[LOG_BUFFER_SIZE];

    va_list args;
    va_start(args, message);
    int len = vsnprintf(buffer, LOG_BUFFER_SIZE, message, args);
    va_end(args);

    if (len >= LOG_BUFFER_SIZE) {
        len = LOG_BUFFER_SIZE - 1;
        buffer[len] = '\0';
    } else {
        return;
    }

    // TODO: Write to UART
}