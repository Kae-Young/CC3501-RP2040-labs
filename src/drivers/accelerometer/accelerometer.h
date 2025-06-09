#pragma once

/// @brief Initialize I2C communication with accelerometer
void accel_init();

void lis3dh_calc_value(uint16_t raw_value, float *final_value);

void lis3dh_read_data(uint8_t reg, float *final_value);