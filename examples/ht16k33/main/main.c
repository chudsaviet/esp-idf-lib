/*
 * Copyright (c) 2022 Timofei Korostelev <timofei_public@dranik.dev>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <memory.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_log.h>
#include <ht16k33.h>

static char *tag = "main";

void app_main()
{
    ESP_LOGI(tag, "HT16K33 example");

    i2c_dev_t dev;
    memset(&dev, 0, sizeof(i2c_dev_t));

    ht16k33_init(
        &dev,
        0,
        CONFIG_EXAMPLE_I2C_FREQUENCY_HZ,
        CONFIG_EXAMPLE_I2C_MASTER_SDA,
        CONFIG_EXAMPLE_I2C_MASTER_SCL,
        HT16K33_DEFAULT_ADDR
    );

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
