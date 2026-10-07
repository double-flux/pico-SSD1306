#include "SSD1306.h"
#include "pico/stdlib.h"



SSD1306::SSD1306(i2c_inst_t *i2c, uint8_t sda_pin, uint8_t scl_pin, uint8_t i2c_address)
{
    this->i2c = i2c;
    this->sda_pin = sda_pin;
    this->scl_pin = scl_pin;
    this->i2c_address = i2c_address;

    i2c_init(this->i2c, 400 * 1000);
    gpio_set_function(this->sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(this->scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(this->sda_pin);
    gpio_pull_up(this->scl_pin);

    sleep_ms(500);
    this->screen_init();
}



void SSD1306::write(uint8_t *buffer, int length)
{
    // 100ms limit.
    int result = i2c_write_timeout_us(this->i2c, this->i2c_address, buffer, length, false, 100000);
}



void SSD1306::screen_init()
{
    uint8_t params[] =
    {
        0x00, // See the docs, this corresponds to a sequence of commands.
        0xae, // Display off.
        0x20, 0x00, // Horizontal addressing mode.
        0xd5, 0x80, // Set display clock divide ratio/oscillator frequency. This is the recommended default (from AI).
        0xa8, 0x3f, // Set multiplex ratio to 64 (64 px high display).
        0xd3, 0x00, // No vertical display offset.
        0x40, // Set start line address to 0.
        0x8d, 0x14, // Enable the charge pump regulator.
        0xd9, 0xf1, // Set the pre-charge period.
        0xa1, // Segment re-map, seems to be necessary for my device.
        0xc8, // COM re-map, seems to be necessary for my device.
        0xda, 0x12, // Set the com pins hardware configuration. seems to be necessary for my device.
        0x81, 0x80, // Set the brightness (contrast).
        0xdb, 0x40, // Set the VCOMH deselect level. Recommended value from AI.
        0xa4, // Entire display on (display RAM contents).
        0xa6, // Set normal display (not colour inverted).
        0xaf  // Force all pixels on.
    };

    this->write(params, sizeof(params));
}
