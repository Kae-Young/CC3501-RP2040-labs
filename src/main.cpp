#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"

#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"
#include "drivers/led/led.h"

#define LED_PIN 14

int main()
{
    stdio_init_all();

    // Initialise PIO0 to control the LED chain
    uint32_t* led_data = led_init(LED_PIN);

    for (;;) {
        // Test the log system
        log(LogLevel::INFORMATION, "Hello world");

        // Turn on the first LED to be a certain colour

        led_data[0] = led_colour(white, 10);
        pio_sm_put_blocking(pio0, 0, led_data[0]);
        sleep_ms(500);

        // Set the first LED off 
        led_data[0] = 0;
        pio_sm_put_blocking(pio0, 0, led_data[0]);
        sleep_ms(500);
    }

    return 0;
}
