#pragma once

/// Initialise PIO0 to control the LED chain
void led_init(int led_pin);

/// Encode rgb value to uint32_t for PIO control
uint32_t led_colour(int r, int g, int b);