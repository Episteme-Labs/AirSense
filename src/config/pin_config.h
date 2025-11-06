/**
 * @file pin_config.h
 * @author trung.la
 * @date November 06 2025
 * @brief Pin configuration definitions for the Pico W board
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs Company. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages
 */

#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#define PMS_UART uart1               // UART instance for PMS7003
#define PMS_TX_PIN 0              // GPIO pin of Pico W for PMS7003 TX
#define PMS_RX_PIN 1              // GPIO pin of Pico W for PMS7003 RX
#define PMS_SET_PIN 2             // GPIO pin of Pico W for PMS7003 SET
#define PMS_RESET_PIN 3           // GPIO pin of Pico W for PMS7003 RESET

#endif // PIN_CONFIG_H