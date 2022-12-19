#include "screen.h"

#if ST7789
const struct st7789_config lcd_config = {
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


#elif LILYGO_TTGO
const struct st7789_config lcd_config = {
    .spi      = PICO_DEFAULT_SPI_INSTANCE,
    .gpio_din = 3,
    .gpio_clk = 2,
    .gpio_cs  = 5,
    .gpio_dc  = 1,
    .gpio_rst = 0,
    .gpio_bl  = 4,
};

#define MEMORY_WIDTH 320
#define MEMORY_HEIGHT 240

#define LCD_WIDTH 160
#define LCD_HEIGHT 120
#endif

void I_initScreen(void) {
#if ST7789
    // width and height only come into play for fills so let's just pass the memory size instead of LCD size
    st7789_init(&lcd_config, MEMORY_WIDTH, MEMORY_HEIGHT);
    st7789_fill(0x0000);
#elif LILYGO_TTGO
    gpio_init(22);
    gpio_set_dir(22, GPIO_OUT);
    gpio_put(22, 1);
    // width and height only come into play for fills so let's just pass the memory size instead of LCD size
    st7789_init(&lcd_config, MEMORY_WIDTH, MEMORY_HEIGHT);
    st7789_fill(0x0000);
#endif
}

// void I_handleFrame(uint8_t frame) {
//     // no-op for now
// }
uint16_t downscaled_line[DOOM_WIDTH/2];

void I_handleScanline(uint16_t *line, int scanline) {
#if ST7789 || LILYGO_TTGO
    if (scanline % 2 == 0) {
        return;
    }

    for (uint8_t i=0; i < DOOM_WIDTH/2; i++) {
        downscaled_line[i] = line[i*2];
    }
    // st7789_set_cursor((MEMORY_WIDTH - LCD_WIDTH) / 2, (MEMORY_HEIGHT - LCD_HEIGHT) / 2 + (scanline / (MEMORY_HEIGHT / LCD_HEIGHT)));
    st7789_set_cursor((MEMORY_WIDTH - LCD_WIDTH) / 2, (MEMORY_HEIGHT - LCD_HEIGHT) / 2 + (scanline / 2));
    // st7789_write(downscaled_line, sizeof(downscaled_line));
    for (int x = 0; x < DOOM_WIDTH/2; x++) {
        st7789_put(downscaled_line[x]);
        // st7789_write(&downscaled_line[x], sizeof(uint16_t)*8);
    }
#endif
}