/**
 * File: mqtt_client.h
 * Author: trung.la
 * Date: November 08 2025
 * Description: Header file for MQTT client, defining data structures and function prototypes for MQTT interaction on Raspberry Pi Pico.
 *
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 */

#ifndef NETWORK_MQTT_CLIENT_H
#define NETWORK_MQTT_CLIENT_H

#include <stdbool.h>

#include "pm2_5.h"

/**
 * Initialize the MQTT client.
 */
bool init_mqtt_client();

/**
 * Deinitialize the MQTT client.
 */
void deinit_mqtt_client();

/**
 * Subscribe to necessary MQTT topics.
 */
void topics_subscribe();

/**
 * Unsubscribe from MQTT topics.
 */
void topics_unsubscribe();

/**
 * Subscribe to a specific MQTT topic.
 */
bool subscribe_topic(const char *topic);

/**
 * Unsubscribe from a specific MQTT topic.
 */
bool unsubscribe_topic(const char *topic);

/**
 * Publish PM2.5 sensor data to MQTT broker.
 */
void publish_pm25_sensor(pm25_data_t *data);

/**
 * Check if MQTT client is connected to the broker.
 */
bool is_mqtt_connected();

#endif // NETWORK_MQTT_CLIENT_H
