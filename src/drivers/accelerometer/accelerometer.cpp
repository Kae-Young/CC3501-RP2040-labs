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


    //Verify connection with who am I register

    const uint8_t who_am_i_address = 0x0F;
    const uint8_t expected_who_am_i = 0x33;

    uint8_t data;
    int length = 1;

    if (1 != i2c_write_blocking(I2C_INSTANCE, ACCEL_SAD, &who_am_i_address, length, true))
    {
        log(LogLevel::ERROR, "lis3dh::read_registers: Failed to select WHO_AM_I register address.");
        return;
    }
    
    int bytes_read = i2c_read_blocking(I2C_INSTANCE, ACCEL_SAD, &data, length, false);
    
    if (bytes_read != length) {
        log(LogLevel::ERROR, "lis3dh::read_registers: Failed to read WHO_AM_I data.");
        return;
    }

    if (data != expected_who_am_i)
    {
        log(LogLevel::ERROR, "lis3dh::init_i2c_connection: Failed to verify WHO_AM_I check.");
    }
    
    uint8_t buf[2];

    // Turn normal mode and 1.344kHz data rate on
    const uint8_t CTRL_REG_1 = 0x20;
    buf[0] = CTRL_REG_1;
    buf[1] = 0x97;
    if (1 != i2c_write_blocking(I2C_INSTANCE, ACCEL_SAD, buf, 2, false))
    {
        log(LogLevel::ERROR, "lis3dh::write_registers: Failed to select CTRL_REG_1 register address.");
        return;
    }
}