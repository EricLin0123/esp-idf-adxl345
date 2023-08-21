#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
// driver should be included in CMakeLists.txt
#include "driver/i2c.h"

#include "adxl345.h"

#define TAG "ADXL345"

void adxl345_i2c_master_init(int16_t sda, int16_t scl)
{
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = sda,
        .scl_io_num = scl,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ};
    ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &i2c_config));
    // master mode only, no buffer RX/TX needed
    ESP_ERROR_CHECK(i2c_driver_install(I2C_MASTER_NUM, I2C_MODE_MASTER, 0, 0, 0));
}

void adxl345_set_measure_mode()
{
    uint8_t buf[2];
    esp_err_t ret;
    // check device id
    uint8_t ADXL345_DEVID[2];
    ADXL345_DEVID[0] = ADXL345_REG_DEVID & 0xFF;
    ADXL345_DEVID[1] = (ADXL345_REG_DEVID >> 8) & 0xFF;
    ret = i2c_master_write_read_device(I2C_MASTER_NUM, ADXL345_DEFAULT_ADDRESS, &ADXL345_DEVID[0], 2, &buf[0], 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    if (ret == ESP_OK)
    {
        ESP_LOGI(TAG, "devid=%x", buf[0]);
    }
    else
    {
        ESP_LOGE(TAG, "%s", "ESP_FAIL while reading devid");
    }
    // set ADXL345 to measure mode
    buf[0] = ADXL345_REG_POWER_CTL;
    // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable
    buf[1] = 0x08;
    ret = i2c_master_write_to_device(I2C_MASTER_NUM, ADXL345_DEFAULT_ADDRESS, &buf[0], sizeof(buf), I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    if (ret == ESP_OK)
    {
        ESP_LOGI(TAG, "%s", "ADXL345 set to measure mode");
    }
    else
    {
        ESP_LOGE(TAG, "%s", "ESP_FAIL while setting ADXL345 to measure mode");
    }
}