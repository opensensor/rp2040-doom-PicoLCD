#include "st7789_240_135.h"

static const struct st7789_config lcd_config = {
        .spi      = spi1,
        .gpio_din = 11,
        .gpio_clk = 10,
        .gpio_cs  = 9,
        .gpio_dc  = 8,
        .gpio_rst = 12,
        .gpio_bl  = 13,
};

void st7789_240_135_initScreen(void) {
    st7789_init(&lcd_config, LCD_WIDTH, LCD_HEIGHT);

    // Fill the entire screen with black color at the end of initialization
    st7789_fill(0x0000);
}

void st7789_240_135_handleFrameStart(uint8_t frame) {
    // No need to do anything here
}

void st7789_240_135_handleScanline(uint16_t *line, int scanline) {
    uint16_t scaled_line[LCD_WIDTH];
    uint32_t scale_x = (SCREENWIDTH << 16) / LCD_WIDTH;
    uint32_t scale_y = (SCREENHEIGHT << 16) / LCD_HEIGHT;
    uint32_t offset_y = (LCD_HEIGHT - ((SCREENHEIGHT * LCD_WIDTH) / SCREENWIDTH)) / 2;

    uint32_t dst_y = offset_y + ((scanline * scale_y) >> 16);

    if (dst_y < LCD_HEIGHT) {
        for (uint16_t x = 0; x < LCD_WIDTH; x++) {
            uint32_t src_x = (x * scale_x) >> 16;
            if (src_x < SCREENWIDTH) {
                scaled_line[x] = line[src_x];
            } else {
                scaled_line[x] = 0; // Fill with black color for out-of-bounds pixels
            }
        }
        st7789_set_cursor(0, dst_y);
        st7789_write(scaled_line, LCD_WIDTH * sizeof(uint16_t));
    }
}