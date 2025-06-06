#pragma once

/// Initialise PIO0 to control the LED chain
/// Returns a pointer to an led data array
uint32_t* led_init(int led_pin);

/// Represents possible preconfigured colours
enum colour {
    blue,
    red,
    green,
    white,
    off,
    custom
};

/// Encode rgb value to uint32_t for PIO control
uint32_t led_colour(colour colour = custom, int brightness = 255, int r = 0, int g = 0, int b = 0);