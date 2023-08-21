#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "adxl345.h"

static const char *TAG1 = "ADXL345";
static const char *TAG = "SYSTEM";

void app_main(void)
{
    ESP_LOGI(TAG, "INTERFACE is i2c");
    ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d", I2C_MASTER_SDA_IO);
    ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d", I2C_MASTER_SCL_IO);
    adxl345_i2c_master_init(I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO);
    adxl345_set_measure_mode();
    uint8_t buf[8];
    uint8_t addrs[6] = {
        ADXL345_REG_DATAX0,
        ADXL345_REG_DATAX1,
        ADXL345_REG_DATAY0,
        ADXL345_REG_DATAY1,
        ADXL345_REG_DATAZ0,
        ADXL345_REG_DATAZ1};
    int i;
    // measure all three axes of adxl345
    while (1)
    {
        // adxl345 measure
        for (i = 0; i <= 5; i++)
        {
            i2c_master_write_read_device(I2C_MASTER_NUM, ADXL345_DEFAULT_ADDRESS, &addrs[i], 1, &buf[i], 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
        }
        ESP_LOGI(TAG1, "x=%d, y=%d, z=%d", (int16_t)(buf[1] << 8 | buf[0]), (int16_t)(buf[3] << 8 | buf[2]), (int16_t)(buf[5] << 8 | buf[4]));
        i = 0;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}