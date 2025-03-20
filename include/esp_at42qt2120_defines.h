#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file esp_at42qt2120_defines.h
 * @brief Register definitions for the AT42QT2120 touch sensor IC.
 * 
 * This file contains register definitions for the AT42QT2120 touch controller.
 * It defines register addresses for control, calibration, status monitoring, etc.
 * over an I2C interface.
 */

/* ------------------ Device Address ------------------ */
/** @brief AT42QT2120 I2C slave address (fixed and not changeable) */
#define AT42QT2120_SLAVE_ADDRESS 0x1C

/* ------------------ General Registers ------------------ */
/** @brief Register storing the chip ID (Always 0x3E) */
#define AT42QT2120_REG_CHIP_ID 0x00
/** @brief Firmware version number */
#define AT42QT2120_REG_FIRMWARE_VERSION 0x01
/** @brief Stores bits indicating overall detection status */
#define AT42QT2120_REG_DETECTION_STATUS 0x02
/** @brief Key status register for keys 0-7 */
#define AT42QT2120_REG_KEY_STATUS_07_00 0x03
/** @brief Key status register for keys 8-11 */
#define AT42QT2120_REG_KEY_STATUS_11_08 0x04
/** @brief Slider position register (0-255) */
#define AT42QT2120_REG_SLIDER_POSITION 0x05
/** @brief Initiates a calibration cycle when written to */
#define AT42QT2120_REG_CALIBRATE 0x06
/** @brief Initiates a reset cycle when written to */
#define AT42QT2120_REG_RESET 0x07
/** @brief Low power mode register setting */
#define AT42QT2120_REG_LOW_POWER_MODE 0x08
/** @brief Toward touch drift register (default: 20/3.2s) */
#define AT42QT2120_REG_TTD_MODE 0x09
/** @brief Away from touch drift register (default: 5/0.8s) */
#define AT42QT2120_REG_ATD_MODE 0x0A
/** @brief Number of measurements required to confirm key press (default: 4) */
#define AT42QT2120_REG_DETECTION_INTEGRATOR 0x0B
/** @brief Touch recalibration delay */
#define AT42QT2120_REG_TOUCH_RECAL_DELAY 0x0C
/** @brief Drift hold time */
#define AT42QT2120_REG_DRIFT_HOLD_TIME 0x0D
/** @brief Enables/disables slider or wheel function (disabled by default) */
#define AT42QT2120_REG_SLIDER_OPTIONS 0x0E
/** @brief Charge time register setting */
#define AT42QT2120_REG_CHARGE_TIME 0x0F

/* ------------------ Key Threshold Registers ------------------ */
/** @brief Detection threshold per key */
#define AT42QT2120_REG_KEY_00_DTHR 0x10
#define AT42QT2120_REG_KEY_01_DTHR 0x11
#define AT42QT2120_REG_KEY_02_DTHR 0x12
#define AT42QT2120_REG_KEY_03_DTHR 0x13
#define AT42QT2120_REG_KEY_04_DTHR 0x14
#define AT42QT2120_REG_KEY_05_DTHR 0x15
#define AT42QT2120_REG_KEY_06_DTHR 0x16
#define AT42QT2120_REG_KEY_07_DTHR 0x17
#define AT42QT2120_REG_KEY_08_DTHR 0x18
#define AT42QT2120_REG_KEY_09_DTHR 0x19
#define AT42QT2120_REG_KEY_10_DTHR 0x1A
#define AT42QT2120_REG_KEY_11_DTHR 0x1B

/* ------------------ Key Control Registers ------------------ */
/** @brief Control settings per key */
#define AT42QT2120_REG_KEY_00_CTRL 0x1C
#define AT42QT2120_REG_KEY_01_CTRL 0x1D
#define AT42QT2120_REG_KEY_02_CTRL 0x1E
#define AT42QT2120_REG_KEY_03_CTRL 0x1F
#define AT42QT2120_REG_KEY_04_CTRL 0x20
#define AT42QT2120_REG_KEY_05_CTRL 0x21
#define AT42QT2120_REG_KEY_06_CTRL 0x22
#define AT42QT2120_REG_KEY_07_CTRL 0x23
#define AT42QT2120_REG_KEY_08_CTRL 0x24
#define AT42QT2120_REG_KEY_09_CTRL 0x25
#define AT42QT2120_REG_KEY_10_CTRL 0x26
#define AT42QT2120_REG_KEY_11_CTRL 0x27

/* ------------------ Key Pulse Scale Registers ------------------ */
/** @brief Pulse scale settings per key */
#define AT42QT2120_REG_KEY_00_PULSE_SCALE 0x28
#define AT42QT2120_REG_KEY_01_PULSE_SCALE 0x29
#define AT42QT2120_REG_KEY_02_PULSE_SCALE 0x2A
#define AT42QT2120_REG_KEY_03_PULSE_SCALE 0x2B
#define AT42QT2120_REG_KEY_04_PULSE_SCALE 0x2C
#define AT42QT2120_REG_KEY_05_PULSE_SCALE 0x2D
#define AT42QT2120_REG_KEY_06_PULSE_SCALE 0x2E
#define AT42QT2120_REG_KEY_07_PULSE_SCALE 0x2F
#define AT42QT2120_REG_KEY_08_PULSE_SCALE 0x30
#define AT42QT2120_REG_KEY_09_PULSE_SCALE 0x31
#define AT42QT2120_REG_KEY_10_PULSE_SCALE 0x32
#define AT42QT2120_REG_KEY_11_PULSE_SCALE 0x33

/* ------------------ Key Signal Registers (MSB & LSB) ------------------ */
/** @brief Signal values per key */
#define AT42QT2120_REG_KEY_00_MSB_SIGNAL 0x34
#define AT42QT2120_REG_KEY_00_LSB_SIGNAL 0x35
#define AT42QT2120_REG_KEY_01_MSB_SIGNAL 0x36
#define AT42QT2120_REG_KEY_01_LSB_SIGNAL 0x37
#define AT42QT2120_REG_KEY_02_MSB_SIGNAL 0x38
#define AT42QT2120_REG_KEY_02_LSB_SIGNAL 0x39
#define AT42QT2120_REG_KEY_03_MSB_SIGNAL 0x3A
#define AT42QT2120_REG_KEY_03_LSB_SIGNAL 0x3B
#define AT42QT2120_REG_KEY_04_MSB_SIGNAL 0x3C
#define AT42QT2120_REG_KEY_04_LSB_SIGNAL 0x3D
#define AT42QT2120_REG_KEY_05_MSB_SIGNAL 0x3E
#define AT42QT2120_REG_KEY_05_LSB_SIGNAL 0x3F
#define AT42QT2120_REG_KEY_06_MSB_SIGNAL 0x40
#define AT42QT2120_REG_KEY_06_LSB_SIGNAL 0x41
#define AT42QT2120_REG_KEY_07_MSB_SIGNAL 0x42
#define AT42QT2120_REG_KEY_07_LSB_SIGNAL 0x43
#define AT42QT2120_REG_KEY_08_MSB_SIGNAL 0x44
#define AT42QT2120_REG_KEY_08_LSB_SIGNAL 0x45
#define AT42QT2120_REG_KEY_09_MSB_SIGNAL 0x46
#define AT42QT2120_REG_KEY_09_LSB_SIGNAL 0x47
#define AT42QT2120_REG_KEY_10_MSB_SIGNAL 0x48
#define AT42QT2120_REG_KEY_10_LSB_SIGNAL 0x49
#define AT42QT2120_REG_KEY_11_MSB_SIGNAL 0x4A
#define AT42QT2120_REG_KEY_11_LSB_SIGNAL 0x4B

/* ------------------ Key Reference Data Registers (MSB & LSB) ------------------ */
/** @brief Reference Data values per key */
#define AT42QT2120_REG_KEY_00_MSB_REFERENCE 0x4C
#define AT42QT2120_REG_KEY_00_LSB_REFERENCE 0x4D
#define AT42QT2120_REG_KEY_01_MSB_REFERENCE 0x4E
#define AT42QT2120_REG_KEY_01_LSB_REFERENCE 0x4F
#define AT42QT2120_REG_KEY_02_MSB_REFERENCE 0x50
#define AT42QT2120_REG_KEY_02_LSB_REFERENCE 0x51
#define AT42QT2120_REG_KEY_03_MSB_REFERENCE 0x52
#define AT42QT2120_REG_KEY_03_LSB_REFERENCE 0x53
#define AT42QT2120_REG_KEY_04_MSB_REFERENCE 0x54
#define AT42QT2120_REG_KEY_04_LSB_REFERENCE 0x55
#define AT42QT2120_REG_KEY_05_MSB_REFERENCE 0x56
#define AT42QT2120_REG_KEY_05_LSB_REFERENCE 0x57
#define AT42QT2120_REG_KEY_06_MSB_REFERENCE 0x58
#define AT42QT2120_REG_KEY_06_LSB_REFERENCE 0x59
#define AT42QT2120_REG_KEY_07_MSB_REFERENCE 0x5A
#define AT42QT2120_REG_KEY_07_LSB_REFERENCE 0x5B
#define AT42QT2120_REG_KEY_08_MSB_REFERENCE 0x5C
#define AT42QT2120_REG_KEY_08_LSB_REFERENCE 0x5D
#define AT42QT2120_REG_KEY_09_MSB_REFERENCE 0x5E
#define AT42QT2120_REG_KEY_09_LSB_REFERENCE 0x5F
#define AT42QT2120_REG_KEY_10_MSB_REFERENCE 0x60
#define AT42QT2120_REG_KEY_10_LSB_REFERENCE 0x61
#define AT42QT2120_REG_KEY_11_MSB_REFERENCE 0x62
#define AT42QT2120_REG_KEY_11_LSB_REFERENCE 0x63

#ifdef __cplusplus
}
#endif