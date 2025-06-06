#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"

#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"
#include "led.h"

uint32_t* led_init(int led_pin)
{
    // Initialise PIO0 to control the LED chain
    uint pio_program_offset = pio_add_program(pio0, &ws2812_program);
    ws2812_program_init(pio0, 0, pio_program_offset, led_pin, 800000, false);

    // Initialise led data array
    static uint32_t led_data[12];
    for (int i = 0; i < 12; i++)
    {
        led_data[i] = 0;
    }
    
    return led_data;
}

uint32_t led_colour(colour colour, int brightness, int r, int g, int b)
{
    switch (colour)
    {
    case red:
        r = 1 * brightness;
        g = 0 * brightness;
        b = 0 * brightness;
        break;
    
    case green:
        r = 0 * brightness;
        g = 1 * brightness;
        b = 0 * brightness;
        break;
    
    case blue:
        r = 0 * brightness;
        g = 0 * brightness;
        b = 1 * brightness;
        break;
    
    case white:
        r = 1 * brightness;
        g = 1 * brightness;
        b = 1 * brightness;
        break;
    
    case off:
        r = 0 * brightness;
        g = 0 * brightness;
        b = 0 * brightness;
        break;
    
    default:
        break;
    }
    return (r << 24) | (g << 16) | (b << 8);
}

uint32_t* led_set(int led_num, uint32_t* led_data, uint32_t value)
{
    led_data[led_num-1] = value;
    return led_data;
}