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

#define LCD_WIDTH 240
#define LCD_HEIGHT 135

static uint8_t current_downsampled_row = 0;
static uint16_t downsampled_row[DOWNSAMPLING_FACTOR_OUT_OF_100 / 100][DOWNSAMPLED_WIDTH]; // I have no idea why I can't do (int)DOWNSAMPLED_WIDTH
static uint16_t downsampled_column[DOWNSAMPLING_FACTOR_OUT_OF_100 / 100];

void st7789_240_135_initScreen(void) {
    // width and height only come into play for fills so let's just pass the memory size instead of LCD size
    st7789_init(&lcd_config, MEMORY_WIDTH, MEMORY_HEIGHT);
    st7789_fill(0x0000);

    // st7789_partial_area(80,240);
}

void st7789_240_135_handleFrameStart(uint8_t frame) {
    current_downsampled_row = 0;
}

void downsample_y_and_blit(int scanline) {
    st7789_set_cursor((MEMORY_WIDTH - LCD_WIDTH) / 2, (MEMORY_HEIGHT - LCD_HEIGHT) / 2 + (scanline * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100));
    for (uint16_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
        for (uint8_t y = 0; y < (DOWNSAMPLING_FACTOR_OUT_OF_100 / 100); y++) {
            downsampled_column[y] = downsampled_row[y][x];
        }

        st7789_put(downsample_pixel_group(downsampled_column));
    }

    current_downsampled_row = 0;
}

void st7789_240_135_handleScanline(uint16_t *line, int scanline) {
    // downsample_line(line, downsampled_row[current_downsampled_row++]);
    
    // st7789_set_cursor((MEMORY_WIDTH - LCD_WIDTH) / 2, (MEMORY_HEIGHT - LCD_HEIGHT) / 2 + (scanline * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100));

    // for (int x = 0; x < DOWNSAMPLED_WIDTH; x++) {
    //     st7789_put(downsampled_row[0][x]);
    //     // st7789_write(&line[x], sizeof(uint16_t));
    // }

    downsample_line(line, downsampled_row[current_downsampled_row++]);
    // current_downsampled_row += 1;

    if ((current_downsampled_row * 100) >= DOWNSAMPLING_FACTOR_OUT_OF_100) {
        downsample_y_and_blit(scanline);
    } 
}