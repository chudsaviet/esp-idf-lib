/*
 * Copyright (c) YYYY YOUR NAME HERE <user@your.dom.ain>
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

#include <freertos/FreeRTOS.h>

#include <esp_err.h>
#include <esp_log.h>

#include "ht16k33.h"

static char *tag = "ht16k33";


esp_err_t ht16k33_init_desc(i2c_dev_t *dev, i2c_port_t port,
        gpio_num_t sda_gpio, gpio_num_t scl_gpio, uint8_t addr)
{
    return ESP_ERR_NOT_SUPPORTED;
}


