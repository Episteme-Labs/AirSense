#include <stdio.h>
#include "pico/stdlib.h"
#include "pm2_5.h"

int main()
{
    stdio_init_all();
    
    // Initialize PM2.5 sensor with default (real hardware) HAL
    pm25_sensor_init(NULL);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
