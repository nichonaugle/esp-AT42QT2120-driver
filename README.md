# AT42QT2120 ESP-IDF Driver

## Overview
This repository contains an ESP-IDF driver for the AT42QT2120 capacitive touch sensor. The driver allows communication with the AT42QT2120 over I2C and provides functions for reading touch detection, slider position, and configuring device settings.

### Device Datasheet
For detailed specifications and register descriptions, refer to the [AT42QT2120 datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/doc9634.pdf).

## Files
- **`esp_at42qt2120_defines.h`**: Contains register definitions for the AT42QT2120.
- **`esp_at42qt2120_driver.h`**: Defines the driver interface and function prototypes.
- **`esp_at42qt2120_driver.c`**: Implements the driver functions for reading/writing registers and controlling the device.

## Features
- I2C communication with AT42QT2120
- Basic read and write functions that handle I2C protocol
- Read detection status and slider position
- Enable/disable slider and wheel mode
- Perform device calibration and reset

## Usage
### Initialization
To initialize the AT42QT2120, call the `at42qt2120_init()` function with the I2C bus handle and device configuration parameters.

```c
at42qt2120_handle_t at42qt2120;
i2c_master_bus_handle_t i2c_bus;
at42qt2120_init(&i2c_bus, &at42qt2120, 400000, 1000);
```

### Reading Detection Status
```c
uint8_t status;
at42qt2120_read_detection_status(&at42qt2120, &status);
```

### Reading Slider Position
```c
uint8_t position;
at42qt2120_read_slider_position(&at42qt2120, &position);
```

### Calibration and Reset
```c
at42qt2120_calibrate(&at42qt2120);
at42qt2120_reset(&at42qt2120);
```

### Enabling/Disabling Slider or Wheel
```c
at42qt2120_enable_slider(&at42qt2120);
at42qt2120_enable_wheel(&at42qt2120);
at42qt2120_disable_slider_wheel(&at42qt2120);
```

## Dependencies
This driver requires the ESP-IDF framework and includes dependencies on:
- `driver/i2c_master.h`
- `freertos/FreeRTOS.h`
- `freertos/task.h`
- `esp_err.h`
- `esp_log.h`

## License
This project is licensed under the MIT License.

## Author(s)
Developed by Sean Daniel Celerio and Tayte Choudhury