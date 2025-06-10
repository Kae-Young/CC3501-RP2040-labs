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

    

    printf("Hello");
    accel_init();
    while (true)
    {
        

        sleep_ms(500);

    }

    return 0;
}
