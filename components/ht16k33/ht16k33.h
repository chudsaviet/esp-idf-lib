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

/**
 * @file ht16k33.h
 * @defgroup example example
 * @{
 *
 * HT16K33 LED Controller driver.
 * No keyscan features implemented.
 *
 */

#if !defined(__HT16K33_H__)
#define __HT16K33_H__

#ifdef __cplusplus

extern "C" {
#endif

#define HT16K33_DEFAULT_ADDR 0x70

#include <esp_err.h>
#include <driver/gpio.h>

#include <i2cdev.h>

/**
 * @brief Initialize HT16K33 device descriptor
 *
 * @param dev output I2C device descriptor
 * @param port I2C port
 * @param sda_gpio SDA GPIO
 * @param scl_gpio SCL GPIO
 * @param addr device I2C address
 * @return ESP_OK in case of success
 */
esp_err_t ht16k33_init_desc(i2c_dev_t *dev, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio, uint8_t addr);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif // __HT16K33__H__
