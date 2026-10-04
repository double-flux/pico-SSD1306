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
}



void SSD1306::write(uint8_t *buffer, int length)
{
    // 100ms limit.
    int result = i2c_write_timeout_us(this->i2c, this->i2c_address, buffer, length, false, 100000);
}