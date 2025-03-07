#include "esp_at42qt2120_driver.h"

/* Defined preset I2C compatible address (IS NOT BE CHANGEABLE) */
#define AT42QT2120_SLAVE_ADDRESS 0x1C

/* Defined Registers for AT42QT2120 */
#define AT42QT2120_REG_CHIP_ID 0x00             // Register that stores the chip ID (IS ALWAYS 0x3E)
#define AT42QT2120_REG_DETECTION_STATUS 0x02    // Register that stores bits that indicate individual status
#define AT42QT2120_REG_SLIDER_POSITION 0x05     // Register that stores the slider value (0-255)
#define AT42QT2120_REG_CALIBRATE 0x06           // Register that drives calibration cycle if written to
#define AT42QT2120_REG_RESET 0x07               // Register that drives reset cycle if written to
#define AT42QT2120_REG_SLIDER_OPTIONS 0x0E      // Register that determines if a slider/wheel is enabled (disabled by default)