/* Play music from Bluetooth device

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "audio_element.h"
#include "audio_pipeline.h"
#include "audio_event_iface.h"
#include "audio_common.h"
#include "i2s_stream.h"
#include "esp_peripherals.h"
#include "periph_touch.h"
#include "audio_hal.h"
#include "board.h"
#include "bluetooth_service.h"
#include "periph_button.h"

static const char *TAG = "BLUETOOTH_EXAMPLE";

// #define LYRAT_TOUCH_SET     TOUCH_PAD_NUM9
// #define LYRAT_TOUCH_PLAY    TOUCH_PAD_NUM8
// #define LYRAT_TOUCH_VOLUP   TOUCH_PAD_NUM7
// #define LYRAT_TOUCH_VOLDWN  TOUCH_PAD_NUM4

void app_main(void)
{
    audio_pipeline_handle_t pipeline;

    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    audio_hal_codec_config_t codec_config = AUDIO_HAL_ES8388_DEFAULT();
    audio_hal_handle_t hal_handle = audio_hal_init(&codec_config, 2);
    audio_hal_ctrl_codec(hal_handle, AUDIO_HAL_CODEC_MODE_DECODE, AUDIO_HAL_CTRL_START);

    audio_pipeline_cfg_t pipeline_config = DEFAULT_AUDIO_PIPELINE_CONFIG();
    pipeline = audio_pipeline_init(&pipeline_config);

    i2s_stream_cfg_t i2s_cfg = I2S_STREAM_CFG_DEFAULT();

    audio_element_handle_t i2s_stream_writer = i2s_stream_init(&i2s_cfg);

    bluetooth_service_cfg_t bt_cfg = {
        .device_name = "FUSCAO",
        .mode = BLUETOOTH_A2DP_SINK,
    };

    bluetooth_service_start(&bt_cfg);

    audio_element_handle_t bt_stream_reader = bluetooth_service_create_stream();


    audio_pipeline_register(pipeline, bt_stream_reader, "bt");
    audio_pipeline_register(pipeline, i2s_stream_writer, "i2s");
    audio_pipeline_link(pipeline, (const char *[]){"bt", "i2s"}, 2);


    esp_periph_config_t periph_cfg = {0};
    esp_periph_init(&periph_cfg);

    esp_periph_handle_t bt_periph = bluetooth_service_create_periph();
    esp_periph_start(bt_periph);

    audio_event_iface_cfg_t evt_cfg = AUDIO_EVENT_IFACE_DEFAULT_CFG();
    audio_event_iface_handle_t evt = audio_event_iface_init(&evt_cfg);

    audio_pipeline_set_listener(pipeline, evt);

    audio_event_iface_set_listener(esp_periph_get_event_iface(), evt);
    audio_pipeline_run(pipeline);

    while (1)
    {
        audio_event_iface_msg_t msg;
        audio_event_iface_listen(evt, &msg, portMAX_DELAY);
        if (msg.source_type == AUDIO_ELEMENT_TYPE_ELEMENT && msg.source == (void *)bt_stream_reader && msg.cmd == AEL_MSG_CMD_REPORT_MUSIC_INFO)
        {
            audio_element_info_t music_info = {0};

            audio_element_getinfo(bt_stream_reader, &music_info);

            ESP_LOGI(TAG, "[ * ] Receive music info from Bluetooth, sample_rates=%d, bits=%d, ch=%d",
                     music_info.sample_rates, music_info.bits, music_info.channels);

            audio_element_setinfo(i2s_stream_writer, &music_info);
            i2s_stream_set_clk(i2s_stream_writer, music_info.sample_rates, music_info.bits, music_info.channels);
            continue;
        }
    }
}