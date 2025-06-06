#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"

#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"
#include "drivers/led/led.h"

#define LED_PIN 14

void led_demo(uint32_t* led_data)
{
    for (int i = 1; i < 13; i++)
    {
        led_data = led_set(i, led_data, led_colour(white, 5*i));
        led_write(led_data);
        sleep_ms(50);
    }
    for (int i = 12; i > 0; i--)
    {
        led_data = led_set(i, led_data, led_colour(white));
        led_write(led_data);
        sleep_ms(50);
    }
    for (int i = 0; i < 200; i += 40)
    {
        for (int j = 0; j < 13; j++)
        {
            led_data = led_set(j, led_data, led_colour(custom,0, 255 - i, 255, 255));
        }
        led_write(led_data);
        sleep_ms(60);
    }
    for (int i = 0; i < 200; i += 40)
    {
        for (int j = 0; j < 13; j++)
        {
            led_data = led_set(j, led_data, led_colour(custom,0, 55 + i, 255 - i, 255));
        }
        led_write(led_data);
        sleep_ms(60);
    }
    for (int i = 0; i < 200; i += 40)
    {
        for (int j = 0; j < 13; j++)
        {
            led_data = led_set(j, led_data, led_colour(custom,0, 255, 55 + i, 255 - i));
        }
        led_write(led_data);
        sleep_ms(60);
    }
    for (int i = 0; i < 281; i += 40)
    {
        for (int j = 0; j < 13; j++)
        {
            led_data = led_set(j, led_data, led_colour(custom,0, 255 - i, 255 - i, 55 + i));
        }
        led_write(led_data);
        sleep_ms(60);
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 13; j += 2)
        {
            led_data = led_set(j, led_data, led_colour(blue, 150));
        }
        for (int j = 1; j < 13; j += 2)
        {
            led_data = led_set(j, led_data, led_colour(off));
        }
        led_write(led_data);
        sleep_ms(100);
        for (int j = 1; j < 13; j += 2)
        {
            led_data = led_set(j, led_data, led_colour(red, 150));
        }
        for (int j = 0; j < 13; j += 2)
        {
            led_data = led_set(j, led_data, led_colour(off));
        }
        led_write(led_data);
        sleep_ms(100);
    }
    
}

int main()
{
    stdio_init_all();

    // Initialise PIO0 to control the LED chain
    uint32_t* led_data = led_init(LED_PIN);
    led_demo(led_data);

    sleep_ms(100);
    led_off();

    return 0;
}
