#include <stdio.h>
#include "pico/stdlib.h"
#include "pm2_5.h"
#include "pm2_5_hal.h"

int main()
{
    stdio_init_all();
    
    pm25_hal_t const *hal = pm25_get_default_hal();
    pm25_sensor_init(hal);

    while (true) {
        pm25_data_t data;
        if (pm25_sensor_read(&data)) {
            printf("PM2.5 Concentration in atmostphere environment: %.2f µg/m³, PM2.5 Concentration in standard particle: %.2f µg/m³\n",
                   data.pm2_5_atm / 1.0, data.pm2_5_cf1 / 1.0);
        } else {
            printf("Failed to read PM2.5 data\n");
        }
        sleep_ms(1000);
    }
}
