/**
 * @file pm2_5_hal_mock.h
 * @author trung.la
 * @date November 06 2025
 * @brief Mock HAL header for PM2.5 sensor testing
 * 
 * COPYRIGHT RESERVED, 2025 Episteme Labs. All rights reserved.
 */

#ifndef PM25_HAL_MOCK_H
#define PM25_HAL_MOCK_H

#include "pm2_5_hal.h"

// Get the mock HAL implementation
const pm25_hal_t* pm25_get_mock_hal(void);

#endif // PM25_HAL_MOCK_H
