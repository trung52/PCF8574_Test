#include <stdio.h>
#include "pcf8574_lib.h"
#include <esp_err.h>
#include <esp_log.h>
#include <string.h>

#define HIGH_LEVEL 1
#define LOW_LEVEL 0

esp_err_t pcf8574_initialize(i2c_dev_t *dev, uint8_t addr, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio){
    memset(dev, 0, sizeof(i2c_dev_t));
    esp_err_t error_code;
    error_code = pcf8574_init_desc(dev, addr, port, sda_gpio, scl_gpio);
    if(error_code != ESP_OK){
        ESP_LOGE(__func__, "PCF8574 initialize failed.");
        return error_code;
    }
    ESP_LOGI(__func__, "PCF8574 initialize successfully.");
    return error_code;
}

esp_err_t pcf8574_deInitialize(i2c_dev_t *dev){
    return pcf8574_free_desc(dev);
}

esp_err_t pcf8574_writeAllPort(i2c_dev_t *dev, uint8_t *val){
    return pcf8574_port_write(dev, *val);
}

esp_err_t pcf8574_writePort(i2c_dev_t *dev, uint8_t *val, uint8_t port, bool level){
    if(level == HIGH_LEVEL){
        *val = ((*val) | (1<<port));
        pcf8574_writeAllPort(dev, val);
    }
    else{
        uint8_t _val = (PCF8574_LOG_NO_ERROR ^ (1<<port)); 
        /*Khong dung truc tiep XOR de tranh truong hop port o san trang thai LOW, khi XOR voi 1 se thanh HIGH*/
        *val = ((*val) & _val); 
        pcf8574_writeAllPort(dev, val);
    }
    return ESP_OK;
}