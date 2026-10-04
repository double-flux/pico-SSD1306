#include "hardware/i2c.h"



class SSD1306
{
public:
    SSD1306(i2c_inst_t *i2c, uint8_t sda_pin, uint8_t scl_pin, uint8_t i2c_address);


    static const uint8_t SCREEN_WIDTH = 128;
    static const uint8_t SCREEN_HEIGHT = 64;

private:
    i2c_inst_t *i2c;
    uint8_t sda_pin;
    uint8_t scl_pin;
    uint8_t i2c_address;

    // Extra byte at the start for the control byte that gets sent each time (0x40).
    uint8_t framebuffer[1025];
    void write(uint8_t *buffer, int length);
};
