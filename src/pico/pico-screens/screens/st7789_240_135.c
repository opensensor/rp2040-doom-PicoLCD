#include "st7789_240_135.h"

static const struct st7789_config lcd_config = {
    .spi      = PICO_DEFAULT_SPI_INSTANCE,
    .gpio_din = PICO_DEFAULT_SPI_TX_PIN,
    .gpio_clk = PICO_DEFAULT_SPI_SCK_PIN,
    .gpio_cs  = PICO_DEFAULT_SPI_CSN_PIN,
    .gpio_dc  = 20,
    .gpio_rst = 21,
    .gpio_bl  = 22,
};

#define MEMORY_WIDTH 320
#define MEMORY_HEIGHT 240

#define LCD_WIDTH 160
#define LCD_HEIGHT 120


void st7789_240_135_initScreen(void) {
    // width and height only come into play for fills so let's just pass the memory size instead of LCD size
    st7789_init(&lcd_config, MEMORY_WIDTH, MEMORY_HEIGHT);
    st7789_fill(0x0000);

    // st7789_partial_area(80,240);
}

static uint16_t downscaled_line[DOOM_WIDTH/2];

void st7789_240_135_handleFrameStart(uint8_t frame) {
    // st7789_set_cursor((MEMORY_WIDTH - LCD_WIDTH) / 2,(MEMORY_HEIGHT - LCD_HEIGHT) / 2);
}

void st7789_240_135_handleScanline(uint16_t *line, int scanline) {
    // if (scanline < 20) {
        // return;
    // }

    for (uint8_t i=0; i < DOOM_WIDTH/2; i++) {
        downscaled_line[i] = line[i*2];
    }
    // st7789_set_cursor((MEMORY_WIDTH - LCD_WIDTH) / 2, (MEMORY_HEIGHT - LCD_HEIGHT) / 2 + (scanline / (MEMORY_HEIGHT / LCD_HEIGHT)));
    // if (scanline % 2 == 0) {
        st7789_set_cursor((MEMORY_WIDTH - LCD_WIDTH) / 2, (MEMORY_HEIGHT - LCD_HEIGHT) / 2 + (scanline/2));
    // }
    // st7789_set_cursor(0, scanline);
    // st7789_write(downscaled_line, sizeof(downscaled_line));
    for (int x = 0; x < DOOM_WIDTH; x++) {
        // st7789_put(downscaled_line[x]);
        // st7789_write(&line[x], sizeof(uint16_t));
    }
    // st7789_write(line, 639);
    // if (scanline % 2 == 1) {
        // uint16_t black[DOOM_WIDTH/4] = {0};
        // uint16_t white[DOOM_WIDTH/4] = {0xffff};
        // st7789_write(black, 80);
        // st7789_write(downscaled_line, 320);
        // st7789_set_cursor(0,100);
        st7789_write(downscaled_line, 320);
        // st7789_write(black, 160);
        // st7789_write(black, 80);

    // }
}