#include <stdio.h>
#include "pcf8574_lib.h"
#include "../build/config/sdkconfig.h"
i2c_dev_t* pcf8574;
uint8_t pcf7574_io_val = PCF8574_LOG_NO_ERROR; 

void app_main(void)
{
    esp_err_t error = pcf8574_initialize(pcf8574, CONFIG_PCF8574_I2C_ADDRESS,
                                                  CONFIG_PCF8574_I2C_PORT,
                                                  CONFIG_PCF8574_PIN_NUM_SDA,
                                                  CONFIG_PCF8574_PIN_NUM_SCL);
    
}
