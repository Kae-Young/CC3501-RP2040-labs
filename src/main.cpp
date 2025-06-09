#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"

#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"
#include "drivers/led/led.h"
#include "drivers/board.h"
#include "drivers/accelerometer/accelerometer.h"

int main()
{
    stdio_init_all();

    // Initialise PIO0 to control the LED chain
    uint32_t* led_data = led_init();
    led_demo();

    float x_accel, y_accel, z_accel;

    printf("Hello");
    accel_init();
    while (true)
    {
        lis3dh_read_data(0x28, &x_accel);
        lis3dh_read_data(0x2A, &y_accel);
        lis3dh_read_data(0x2C, &z_accel);

        // Acceleration is read as a multiple of g (gravitational acceleration on the Earth's surface)
        printf("ACCELERATION VALUES: \n");
        printf("X acceleration: %.3fg\n", x_accel);
        printf("Y acceleration: %.3fg\n", y_accel);
        printf("Z acceleration: %.3fg\n", z_accel);

        sleep_ms(500);

        // Clear terminal 
        printf("\033[1;1H\033[2J");
    }

    return 0;
}
