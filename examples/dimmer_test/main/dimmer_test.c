#include <stdio.h>
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "esp_log.h"
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "esp_at42qt2120_driver.h"
#include "esp_at42at2120_defines.h"
#include "iot_button.h"

#define I2C_MASTER_PORT I2C_NUM_0 
#define I2C_MASTER_SDA_IO 6
#define I2C_MASTER_SCL_IO 7
#define NCHANGE_PIN 22

#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_VERBOSE

static const char* TAG = "MAIN";
static at42qt2120_handle_t Slider_Handle;
extern uint8_t LEDs = 0;
extern uint8_t Position = 0;

/* Initializes the I2C bus */
void i2c_bus_init(i2c_master_bus_handle_t* i2c_handle);

/* Initialize the button handles for the change pin */
esp_err_t nchange_button_init(void);

/* Button Handle specific functions */
static void _single_press_event(void *arg, void *usr_data);
static void _track_slider_position(void *arg);
static void _single_click_event(void *arg, void *usr_data);
static void _long_press_event(void *arg, void *usr_data);

void app_main(void) {
    /* Initalize I2C Bus */
    i2c_master_bus_handle_t I2C_Handle;
    i2c_bus_init(&I2C_Handle);

    /* Initalize at42qt2120 device handle */
    at42qt2120_init(&I2C_Handle, &Slider_Handle, 100000, -1);

    /* Reset, Enable, and Calibrate Slider */
    ESP_LOGI(TAG, "Reseting ....");
    at42qt2120_reset(&Slider_Handle);
    ESP_LOGI(TAG, "Enabling Slider ....");
    at42qt2120_enable_slider(&Slider_Handle);
    ESP_LOGI(TAG, "Calibrating ....");
    at42qt2120_calibrate(&Slider_Handle);
    vTaskDelay(pdMS_TO_TICKS(100));

    /* Initialize NCHANGE button handler (Has to be called after slider initialization and setup) */
    nchange_button_init();
    
    /* Constantly output LEDs value */
    for(;;) {
        ESP_LOGI(TAG, "Position: %d, LEDs: %d", Position, LEDs);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

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

esp_err_t nchange_button_init(void) {
    /* Configures change handle by defining nchange pin and active level */
    button_config_t nchange_config = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = NCHANGE_PIN,
            .active_level = 0,
            .disable_pull = false
        }
    };

    /* Initialize nchange handle based on configuration */ 
    button_handle_t nchange_handle = iot_button_create(&nchange_config);
    if (!nchange_handle) {
        ESP_LOGE(TAG, "nchange button creation failed");
        return ESP_ERR_INVALID_STATE;
    }

    /* Register events to functions */
    iot_button_register_cb(nchange_handle, BUTTON_PRESS_DOWN, _single_press_event, NULL);
    iot_button_register_cb(nchange_handle, BUTTON_SINGLE_CLICK, _single_click_event, NULL);
    button_event_config_t long_press_config = {
        .event = BUTTON_LONG_PRESS_START,
        .event_data.long_press = {200} // in milliseconds
    };
    iot_button_register_event_cb(nchange_handle, long_press_config, _long_press_event, NULL);

    return ESP_OK;
}

static void _single_press_event(void *arg, void *usr_data) {
    ESP_LOGI(TAG, "SINGLE PRESS DETECTED");
    
    /* Start a task to monitor slider position while the button is held */
    xTaskCreate(_track_slider_position, "TrackSlider", 2048, NULL, 10, NULL); // This task is needed to prevent blocking _long_press_event()
}

static void _track_slider_position(void *arg) {
    /* While active update read and save slider position */
    while (!gpio_get_level(NCHANGE_PIN)) {
        at42qt2120_read_slider_position(&Slider_Handle, &Position);
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    vTaskDelete(NULL); 
}

static void _single_click_event(void *arg, void *usr_data) {
    ESP_LOGI(TAG, "SINGLE CLICK DETECTED");
    LEDs = Position;
}

static void _long_press_event(void *arg, void *usr_data) {
    ESP_LOGI(TAG, "LONG PRESS DETECTED");
    int16_t velocity = 0;
    uint8_t PrevPosition = Position;
    uint8_t CurrPosition;
    
    while (!gpio_get_level(NCHANGE_PIN)) {
        /* Calculate velocity based on the measured position difference with bound checking */
        CurrPosition = Position;
        if (CurrPosition - PrevPosition < -256) 
            velocity = -255;
        else if (CurrPosition - PrevPosition > 255) 
            velocity = 255;
        else
            velocity = CurrPosition - PrevPosition;

        /* Change LEDs based on the velocity with bound checking */
        if (LEDs + velocity > 255)
            LEDs = 255;
        else if (LEDs + velocity < 0)
            LEDs = 0;
        else 
            LEDs += velocity;
        
        PrevPosition = CurrPosition;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}