#include <stdio.h>
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_at42qt2120_driver.h"
#include "esp_at42at2120_defines.h"

#define I2C_MASTER_PORT I2C_NUM_0 
#define I2C_MASTER_SDA_IO 6
#define I2C_MASTER_SCL_IO 7
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_VERBOSE
#define CONFIG_FREERTOS_HZ 1000

static const char* TAG = "MAIN";

/* Initializes the I2C bus */
void i2c_bus_init(i2c_master_bus_handle_t* i2c_handle) {
    /* Configures I2C bus by defining I2C pins, internal pullups, and clock source */
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_MASTER_PORT,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .flags.enable_internal_pullup = true
    };

    /* Initialize I2C bus based on configuration */ 
    esp_err_t ret = i2c_new_master_bus(&bus_config, i2c_handle);
    if (ret != ESP_OK) 
        ESP_LOGE(TAG, "Failed to initialize I2C bus: %s", esp_err_to_name(ret));
    else 
        ESP_LOGI(TAG, "I2C bus initialized succesfully");
}

void app_main(void) {
    /* Initalize I2C Bus */
    i2c_master_bus_handle_t I2C_Handle;
    i2c_bus_init(&I2C_Handle);

    /* Initalize at42qt2120 device handle */
    at42qt2120_handle_t Slider_Handle;
    at42qt2120_init(&I2C_Handle, &Slider_Handle, 100000, -1);

    /* Reset Slider */
    ESP_LOGI(TAG, "Reseting ....");
    at42qt2120_reset(&Slider_Handle);

    /* Enable Slider */
    ESP_LOGI(TAG, "Enabling Slider ....");
    at42qt2120_enable_slider(&Slider_Handle);

    /* Calibrate */
    ESP_LOGI(TAG, "Calibrating ....");
    at42qt2120_calibrate(&Slider_Handle);
    
    /* Continuously read for slider position */
    uint8_t Position = 0;
    for (;;) {
        at42qt2120_read_slider_position(&Slider_Handle, &Position);
        ESP_LOGI(TAG, "%d", Position);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}