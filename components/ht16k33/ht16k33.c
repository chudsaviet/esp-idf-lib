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

#include <esp_check.h>
#include <esp_err.h>
#include <esp_log.h>

#include "ht16k33.h"

static const char* TAG = "ht16k33";

// All commands are one byte long.
// First 4 bits are command type.
// Last 4 bits are parameters.
#define HT16K33_CMD_RAM_SET_POINTER 0b0100
#define HT16K33_CMD_SYSTEM_SETUP 0b0010
#define HT16K33_CMD_SET_BRIGHTNESS 0b1110
#define HT16K33_CMD_DISPLAY_SETUP 0b1000

#define HT16K33_RAM_SIZE_BYTES 16

esp_err_t zero_ram(i2c_dev_t *dev) {
    // First byte is pointer set command.
    // Other bytes are the RAM values, which are zero.
    uint8_t cmd_seq[HT16K33_RAM_SIZE_BYTES + 1] = {0};
    cmd_seq[0] = HT16K33_CMD_RAM_SET_POINTER << 4 | 0b0000;

    // Send whole command sequence at once.
    I2C_DEV_TAKE_MUTEX(dev);
    I2C_DEV_CHECK(dev, i2c_dev_write(dev, NULL, 0, cmd_seq, sizeof(cmd_seq)));
    I2C_DEV_GIVE_MUTEX(dev);

    return ESP_OK;
}

// Send one-byte command.
esp_err_t send_short_cmd(i2c_dev_t *dev, uint8_t cmd) {
    I2C_DEV_TAKE_MUTEX(dev);
    I2C_DEV_CHECK(dev, i2c_dev_write(dev, NULL, 0, &cmd, sizeof(uint8_t)));
    I2C_DEV_GIVE_MUTEX(dev);

    return ESP_OK;
}

esp_err_t ht16k33_init(i2c_dev_t *dev, i2c_port_t port, uint32_t i2c_freq_hz,
 gpio_num_t sda_gpio, gpio_num_t scl_gpio, uint8_t addr)
{
    memset(dev, 0, sizeof(i2c_dev_t));
    dev->port = port;
    dev->addr = addr;
    dev->cfg.sda_io_num = sda_gpio;
    dev->cfg.scl_io_num = scl_gpio;
    dev->cfg.master.clk_speed = i2c_freq_hz;

    ESP_RETURN_ON_ERROR(i2c_dev_create_mutex(dev), TAG, "Can't initialize I2C mutex.");

    // Enable system oscillator.
    ESP_RETURN_ON_ERROR(
        send_short_cmd(dev, HT16K33_CMD_SYSTEM_SETUP << 4 | 0b0001),
        TAG,
        "Can't start oscillator.");

    // Set display off, no blinking.
    ESP_RETURN_ON_ERROR(
        ht16k33_display_setup(dev, 0, HT16K33_BLINKING_0HZ),
        TAG,
        "Can't set display off, no blinking.");

    // Set half brightness.
    ESP_RETURN_ON_ERROR(
        ht16k33_set_brightness(dev, HT16K33_MAX_BRIGHTNESS / 2),
        TAG,
        "Can't set initial brightness.");

    // RAM initializes with random values. Zero it.
    ESP_RETURN_ON_ERROR(zero_ram(dev), TAG, "Can't zero the RAM.");

    return ESP_OK;
}

esp_err_t ht16k33_free_desc(i2c_dev_t *dev)
{
    return i2c_dev_delete_mutex(dev);
}

esp_err_t ht16k33_set_brightness(i2c_dev_t *dev, uint8_t brightness) {
    if (brightness > 15) {
        ESP_LOGE(TAG, "Brightness shall be set in range 0-15.");
        return ESP_ERR_INVALID_ARG;
    }

    ESP_RETURN_ON_ERROR(
        send_short_cmd(dev, HT16K33_CMD_SET_BRIGHTNESS << 4 | brightness),
        TAG,
        "Can't set brightness.");

    return ESP_OK;
}

esp_err_t ht16k33_display_setup(i2c_dev_t *dev, uint8_t on_flag, uint8_t blinking) {
    // on_flag is 1 bit.
    if (on_flag > 1) {
        ESP_LOGE(TAG, "on_flag can only be 0 or 1.");
        return ESP_ERR_INVALID_ARG;
    }

    // Blinking mode is just 2 bits.
    if (blinking > 0b11) {
        ESP_LOGE(TAG, "Use only HT16K33_BLINKING_* constants.");
        return ESP_ERR_INVALID_ARG;
    }

    ESP_RETURN_ON_ERROR(
        send_short_cmd(dev, HT16K33_CMD_DISPLAY_SETUP << 4 | on_flag << 2 | blinking),
        TAG,
        "Can't do display setup.");

    return ESP_OK;
}