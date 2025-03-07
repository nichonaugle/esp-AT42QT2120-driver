#ifndef ESP_AT42QT2120_DRIVER_H
#define ESP_AT42QT2120_DRIVER_H

#include "esp_err.h"
#include "driver/i2c_master.h"

/**
 * @brief Structure representing a at42qt2120 handle.
 */
typedef struct {
    i2c_device_config_t device_config;      // I2C device configuration (Contains i2c address, address bit length, and clock speed)
    i2c_master_dev_handle_t device_handle;  // I2C device handle
    int transaction_timeout_ms;             // Timeout for I2C transactions in milliseconds
} at42qt2120_handle_t;

/**
 * @brief Initialize a digital potentiometer.
 *
 * @param bus_handle Handle to the I2C master bus.
 * @param at42qt2120_handle Pointer to the at42qt2120 handle structure.
 * @param clock_speed I2C clock speed in Hz.
 * @param time_out Time in ms to wait for I2C response. -1 results in infinite wait time
 * @return esp_err_t ESP_OK on success, otherwise an error code.
 */
esp_err_t at42qt2120_init(i2c_master_bus_handle_t* bus_handle, at42qt2120_handle_t* at42qt2120_handle, size_t clock_speed, int time_out);

/**
 * @brief Read a register from the at42qt2120 device.
 *
 * @param at42qt2120_handle Pointer to the at42qt2120 handle structure.
 * @param reg_to_read Register address to read from.
 * @param read_buf Buffer to store the read data.
 * @param read_buf_size Size of the receive buffer.
 * @return esp_err_t ESP_OK on success, otherwise an error code.
 */
esp_err_t at42qt2120_register_read(at42qt2120_handle_t* at42qt2120_handle, uint8_t reg_to_read, uint8_t* read_buf, uint8_t read_buf_size);

/**
 * @brief Write to a register from the at42qt2120 device.
 *
 * @param at42qt2120_handle Pointer to the at42qt2120 handle structure.
 * @param reg_to_write Register address to write to.
 * @param write_buf Buffer containing data to write.
 * @param write_buf_size Size of the transmit buffer.
 * @return esp_err_t ESP_OK on success, otherwise an error code.
 */
esp_err_t at42qt2120_register_write(at42qt2120_handle_t* at42qt2120_handle, uint8_t reg_to_write, uint8_t* write_buf, uint8_t write_buf_size);

#endif