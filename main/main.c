#include <stdio.h>
#include <stdlib.h>
#include "pcf8574_lib.h"
#include "../build/config/sdkconfig.h"
i2c_dev_t pcf8574;

uint8_t pcf7574_io_val = PCF8574_LOG_NO_ERROR; 

void app_main(void)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(i2cdev_init());
    ESP_ERROR_CHECK_WITHOUT_ABORT(pcf8574_initialize(&pcf8574,CONFIG_PCF8574_I2C_ADDRESS,
                                                              CONFIG_PCF8574_I2C_PORT,
                                                              CONFIG_PCF8574_PIN_NUM_SDA,
                                                              CONFIG_PCF8574_PIN_NUM_SCL));
    // pcf7574_io_val = 0xAA;
    // pcf8574_writeAllPin(&pcf8574, &pcf7574_io_val);
    while (1)
    {
        pcf7574_io_val = 0xAA;
        ESP_ERROR_CHECK_WITHOUT_ABORT(pcf8574_writeAllPort(&pcf8574, &pcf7574_io_val));
        vTaskDelay(1000);
        pcf7574_io_val = 0x55;
        ESP_ERROR_CHECK_WITHOUT_ABORT(pcf8574_writeAllPort(&pcf8574, &pcf7574_io_val));
        vTaskDelay(1000);
    }
    
}
