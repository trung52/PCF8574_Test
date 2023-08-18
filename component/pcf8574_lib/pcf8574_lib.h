/**
 * @file pcf8574_lib.h
 * @author Vu Thanh Trung (20203623)
 * @brief Library for PCF8574
 * We use PCF8574 to control 8 leds to warning device's errors
 * @date 2023-08-15
 * @copyright Copyright (c) 2023
 */
#ifndef PCF8574_LIB_h
#define PCF8574_LIB_h

#include <stddef.h>
#include "../i2cdev/i2cdev.h"
#include "../esp_idf_lib_helpers/esp_idf_lib_helpers.h"
#include <esp_err.h>
#include "../pcf8574/pcf8574.h"

/*
P0 ----> Wifi Error
P1 ----> SD card Error
P2 ----> SPI Error
P3 ----> UART0 Error
P4 ----> UART2/RS485 Error
P5 ----> I2C_1 Error
P6 ----> I2C_2 Error
P7 ----> PWM/IO Error
*/

#define PCF8574_LOG_NO_ERROR  0xFF          //1111 1111
#define PCF8574_LOG_ERROR_WIFI 0xFE         //1111 1110
#define PCF8574_LOG_ERROR_SD_CARD 0xFD      //1111 1101
#define PCF8574_LOG_ERROR_SPI 0xFB          //1111 1011
#define PCF8574_LOG_ERROR_UART0 0xF7        //1111 0111
#define PCF8574_LOG_ERROR_UART2_RS485 0xEF  //1110 1111
#define PCF8574_LOG_ERROR_I2C_1 0xDF        //1101 1111
#define PCF8574_LOG_ERROR_I2C_2 0xBF        //1011 1111
#define PCF8574_LOG_ERROR_PWM_IO 0x7F       //0111 1111


/**
 * @brief Initialize device descriptor
 * 
 * @param[in] dev I2C device descriptor
 * @param[in] addr I2C address
 * @param[in] port I2C port
 * @param[in] sda_gpio SDA GPIO
 * @param[in] scl_gpio SCL GPIO
 * 
 * @return ESP_OK to indicate success
 */
esp_err_t pcf8574_initialize(i2c_dev_t *dev, uint8_t addr, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio);

/**
 * @brief Free device descriptor
 *
 * @param dev Pointer to I2C device descriptor
 * 
 * @return `ESP_OK` on success
 */
esp_err_t pcf8574_deInitialize(i2c_dev_t *dev);

/**
 * @brief Write to all port (P0->P7)
 * 
 * @param[in] dev I2C device descriptor
 * 
 * @param[in] val 8-bit GPIO port value
*/
esp_err_t pcf8574_writeAllPort(i2c_dev_t *dev, uint8_t *val);

/**
 * @brief Write to only 1 port that assigned
 * 
 * @param[in] dev I2C device descriptor
 * 
 * @param[in] val 8-bit GPIO port value
 * 
 * @param[in] port any port that you want to write (change logic) (value in [0,7])
 * 
 * @param[in] level port's logic level that you want to set
*/
esp_err_t pcf8574_writePort(i2c_dev_t *dev, uint8_t *val, uint8_t port, bool level);
#endif