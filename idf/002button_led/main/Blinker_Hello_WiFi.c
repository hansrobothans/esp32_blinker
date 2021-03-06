/* *****************************************************************
 *
 * Download latest Blinker library here:
 * https://github.com/blinker-iot/blinker-freertos/archive/master.zip
 * 
 * 
 * Blinker is a cross-hardware, cross-platform solution for the IoT. 
 * It provides APP, device and server support, 
 * and uses public cloud services for data transmission and storage.
 * It can be used in smart home, data monitoring and other fields 
 * to help users build Internet of Things projects better and faster.
 * 
 * Docs: https://doc.blinker.app/
 *       https://github.com/blinker-iot/blinker-doc/wiki
 * 
 * *****************************************************************
 * 
 * Blinker 库下载地址:
 * https://github.com/blinker-iot/blinker-freertos/archive/master.zip
 * 
 * Blinker 是一套跨硬件、跨平台的物联网解决方案，提供APP端、设备端、
 * 服务器端支持，使用公有云服务进行数据传输存储。可用于智能家居、
 * 数据监测等领域，可以帮助用户更好更快地搭建物联网项目。
 * 
 * 文档: https://doc.blinker.app/
 *       https://github.com/blinker-iot/blinker-doc/wiki
 * 
 * *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"

#include "Blinker.h"

static const char *TAG = "blinker";
#define LED 12

BlinkerButton button1 = {.name = "btn-abc"};
BlinkerNumber number1 = {.name = "num-abc"};

int counter = 0;
bool led_state = 0;

void button1_callback(const char *data)
{
    BLINKER_LOG(TAG, "get button data: %s", data);

    blinker_button_config_t config = {
        .icon = "fas fa-alicorn",
        .color = "0xFF",
        .text1 = "test",
    };
    led_state = !led_state;
    gpio_set_level(LED, led_state);
    printf("%d\n", led_state);
    blinker_button_print(&button1, &config);
    
}

void data_callback(const cJSON *data)
{
    BLINKER_LOG(TAG, "get json data");

    counter++;

    char count[10];
    // sprintf(count, "%d", counter);
    itoa(counter, count, 10);

    blinker_number_config_t config = {
        .value = count,
    };

    blinker_number_print(&number1, &config);
}

void gpio_led_init(void)
{
    gpio_pad_select_gpio(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
}

void app_main()
{
    gpio_led_init();
    BLINKER_DEBUG_ALL();
    
    blinker_button_init(&button1, button1_callback);
    blinker_attach_data(data_callback);

    blinker_init();
    // run();
}
