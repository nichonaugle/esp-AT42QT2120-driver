#include <stdio.h>
#include <esp_err.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/i2c_master.h>

#include "esp_at42qt2120_driver.h"
#include "esp_at42qt2120_defines.h"

static const char* TAG = "esp_at42qt2120_driver";

/**
  * @brief Initializes the AT42QT2120 touch sensor on the I2C bus.
  */
esp_err_t at42qt2120_init(i2c_master_bus_handle_t* bus_handle, at42qt2120_handle_t* at42qt2120_handle, size_t clock_speed, int time_out) {
    /* Error checking for input parameters */
    if (at42qt2120_handle == NULL) {
        ESP_LOGE(TAG, "at42qt2120_handle improperly initialized!");
        return ESP_ERR_INVALID_ARG;
    }

    if (bus_handle == NULL) {
        ESP_LOGE(TAG, "i2c bus is not initialized correctly");
        return ESP_ERR_INVALID_ARG;
    }

    /* Setting up device configuration to add at42qt2120 to i2c bus */
    at42qt2120_handle->device_config.dev_addr_length = I2C_ADDR_BIT_LEN_7;
    at42qt2120_handle->device_config.device_address = AT42QT2120_SLAVE_ADDRESS;
    at42qt2120_handle->device_config.scl_speed_hz = clock_speed;
    at42qt2120_handle->transaction_timeout_ms = time_out;

    esp_err_t ret = i2c_master_bus_add_device(*bus_handle, &at42qt2120_handle->device_config, &at42qt2120_handle->device_handle);
    if (ret != ESP_OK)
        ESP_LOGE(TAG, "Failed to add at42qt2120 to i2c bus");
    else
        ESP_LOGI(TAG, "Added at42qt2120 to i2c bus.");

    return ret;
}

/* Basic Read and Write functions for at42at2120 */
/**
  * @brief Reads a register from the AT42QT2120.
  */
esp_err_t at42qt2120_register_read(at42qt2120_handle_t* at42qt2120_handle, uint8_t reg_to_read, uint8_t* read_buf, uint8_t read_buf_size) {
    /* Error checking for input parameters */
    if (at42qt2120_handle == NULL) {
        ESP_LOGE(TAG, "at42qt2120_handle is NULL!");
        return ESP_ERR_INVALID_ARG;
    }

    if (read_buf == NULL || read_buf_size == 0) {
        ESP_LOGE(TAG, "read_buf is NULL or invalid read_buf_size!!");
        return ESP_ERR_INVALID_ARG;
    }

    return i2c_master_transmit_receive(at42qt2120_handle->device_handle, &reg_to_read, 1, read_buf, read_buf_size, at42qt2120_handle->transaction_timeout_ms);
}

/**
  * @brief Writes data to a register in the AT42QT2120.
  */
esp_err_t at42qt2120_register_write(at42qt2120_handle_t* at42qt2120_handle, uint8_t reg_to_write, uint8_t* write_buf, uint8_t write_buf_size) {
    /* Error checking for input parameters */
    if (at42qt2120_handle == NULL) {
        ESP_LOGE(TAG, "at42qt2120_handle is NULL!");
        return ESP_ERR_INVALID_ARG;
    }

    if (write_buf == NULL || write_buf_size == 0) {
        ESP_LOGE(TAG, "write_buf is NULL or invalid write_buf_size!");
        return ESP_ERR_INVALID_ARG;
    }

    /* Combine reg_to_write and write_buffer into one buffer */
    uint8_t buffer[write_buf_size + 1];
    buffer[0] = reg_to_write;
    for (uint16_t index = 1; index <= write_buf_size; index++)
        buffer[index] = write_buf[index - 1];

    return i2c_master_transmit(at42qt2120_handle->device_handle, buffer, write_buf_size + 1, at42qt2120_handle->transaction_timeout_ms);
}

/* Specific Register Read/Write functions */
esp_err_t at42qt2120_read_detection_status(at42qt2120_handle_t* at42qt2120_handle, uint8_t* status_buf) {
    esp_err_t ret = at42qt2120_register_read(at42qt2120_handle, AT42QT2120_REG_DETECTION_STATUS, status_buf, 1);
    if (ret != ESP_OK) 
        ESP_LOGE(TAG, "Failed to read detection status from at42qt2120 device!");

    return ret;
}

esp_err_t at42qt2120_read_slider_position(at42qt2120_handle_t* at42qt2120_handle, uint8_t* position_buf) {
    esp_err_t ret = at42qt2120_register_read(at42qt2120_handle, AT42QT2120_REG_SLIDER_POSITION, position_buf, 1);
    if (ret != ESP_OK) 
        ESP_LOGE(TAG, "Failed to read slider position from at42qt2120 device!");

    return ret;
}

esp_err_t at42qt2120_calibrate(at42qt2120_handle_t* at42qt2120_handle) {
    /* Write non-zero byte to start reset cycle */
    uint8_t write_buf = 0xFF;
    esp_err_t ret = at42qt2120_register_write(at42qt2120_handle, AT42QT2120_REG_CALIBRATE, &write_buf, 1);
    if (ret != ESP_OK) 
        ESP_LOGE(TAG, "at42qt2120 device failed to calibrate!");
        
    return ret;
}

esp_err_t at42qt2120_reset(at42qt2120_handle_t* at42qt2120_handle) {
    /* Write non-zero byte to start reset cycle */
    uint8_t write_buf = 0xFF;
    esp_err_t ret = at42qt2120_register_write(at42qt2120_handle, AT42QT2120_REG_RESET, &write_buf, 1);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "at42qt2120 device failed to reset!");
        return ret;
    }
    vTaskDelay(pdMS_TO_TICKS(500)); // Delay to ensure reset cycle finishes (~125 ms for reset cycle)

    return ret;
}

esp_err_t at42qt2120_enable_slider(at42qt2120_handle_t* at42qt2120_handle) {
     /* Write 1 to 8th bit to enable slider mode */
     uint8_t write_buf = 0x80;
     esp_err_t ret = at42qt2120_register_write(at42qt2120_handle, AT42QT2120_REG_SLIDER_OPTIONS, &write_buf, 1);
     if (ret != ESP_OK) 
         ESP_LOGE(TAG, "at42qt2120 device failed to enable slider mode!");
      
     return ret;
}

esp_err_t at42qt2120_enable_wheel(at42qt2120_handle_t* at42qt2120_handle) {
    /* Write 1 to 8th and 7th bit to enable slider mode */
    uint8_t write_buf = 0xC0;
    esp_err_t ret = at42qt2120_register_write(at42qt2120_handle, AT42QT2120_REG_SLIDER_OPTIONS, &write_buf, 1);
    if (ret != ESP_OK) 
        ESP_LOGE(TAG, "at42qt2120 device failed to enable wheel mode!");
     
    return ret;
}

esp_err_t at42qt2120_disable_slider_wheel(at42qt2120_handle_t* at42qt2120_handle) {
    /* Write 0 to 8th and 7th bit to disable slider/wheel mode */
    uint8_t write_buf = 0x00;
    esp_err_t ret = at42qt2120_register_write(at42qt2120_handle, AT42QT2120_REG_SLIDER_OPTIONS, &write_buf, 1);
    if (ret != ESP_OK) 
        ESP_LOGE(TAG, "at42qt2120 device failed to diable slider/wheel mode!");
     
    return ret;
}