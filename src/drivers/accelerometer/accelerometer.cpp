#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"

#include "WS2812.pio.h"
#include "drivers/logging/logging.h"
#include "accelerometer.h"
#include "drivers/board.h"
#include "hardware/i2c.h"
#include "drivers/led/led.h"

void accel_init()
{
    i2c_init(I2C_INSTANCE, 400 * 1000);
    gpio_set_function(ACCEL_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(ACCEL_SCL_PIN, GPIO_FUNC_I2C);

    uint8_t who_am_i_address = 0x0F;
    uint8_t expected_who_am_i = 0x33;

    uint8_t data;
    int length = 1;

    if (1 != i2c_write_blocking(I2C_INSTANCE, SAD, &who_am_i_address, length, true))
    {
        log(LogLevel::ERROR, "lis3dh::read_registers: Failed to select register address.");
        return;
    }
    
    int bytes_read = i2c_read_blocking(I2C_INSTANCE, SAD, &data, length, false);
    
    if (bytes_read != length) {
        log(LogLevel::ERROR, "lis3dh::read_registers: Failed to read data.");
        return;
    }

    if (data == expected_who_am_i)
    {
        led_blink();
    }
    
}