/**
 * File: wifi.h
 * Author: trung.la
 * Date: November 08 2025
 * Description: Header file for Wi-Fi driver, defining data structures and function prototypes for Wi-Fi interaction on Raspberry Pi Pico.
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#ifndef NETWORK_WIFI_H
#define NETWORK_WIFI_H

#include <stdbool.h>
#include <stdint.h>

/**
 * Initialize the Wi-Fi module.
 */
bool init_wifi();

/**
 * Start scanning for available Wi-Fi networks.
 * Scan as periodic of 10 seconds.
 * Returns the number of networks found.
 */
int start_wifi_scan();

/**
 * Print the current Wi-Fi status.
 */
void wifi_status();

#endif // NETWORK_WIFI_H
