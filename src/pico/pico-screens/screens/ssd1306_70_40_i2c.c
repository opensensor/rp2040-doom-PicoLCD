#include "ssd1306_70_40_i2c.h"
#include "pico/ssd1306_i2c.h"
#include "shared.h"



    // .spi      = PICO_DEFAULT_SPI_INSTANCE,
    // .gpio_din = PICO_DEFAULT_SPI_TX_PIN,
    // .gpio_clk = PICO_DEFAULT_SPI_SCK_PIN,
    // .gpio_cs  = PICO_DEFAULT_SPI_CSN_PIN,
    // .gpio_dc  = 20,
    // .gpio_rst = 21,
    // .gpio_bl  = 22,
#define START_Y 24
// +3 to center on 70 pixel width screen
#define START_X (28 + 3)

static ssd1306_t disp;


void ssd1306_70_40_i2c_initScreen(void) {
    disp.external_vcc=false;

    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(22, GPIO_FUNC_I2C);
    gpio_set_function(23, GPIO_FUNC_I2C);
    bi_decl(bi_2pins_with_func(22, 23, GPIO_FUNC_I2C));
    gpio_pull_up(22);
    gpio_pull_up(23);
    
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);

    ssd1306_draw_line(&disp, 28, 20, 98, 20);
    ssd1306_show(&disp);
}

void ssd1306_70_40_i2c_handleFrameStart(uint8_t frame) {
    ssd1306_clear(&disp);
}

void ssd1306_70_40_i2c_blit(uint16_t* downsampled_line, int scanline) {
    // this converts the line to "monochrome" greyscale
    // ditherDownsampledLine(downsampled_line);
    for (uint16_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
        uint16_t downsampled_pixel = downsampled_line[x];
        
        // comment out if using dithering
        downsampled_pixel = colorToGreyscale(downsampled_pixel);

        
        if (downsampled_pixel > 127) {
            ssd1306_draw_pixel(&disp, START_X + x, START_Y + scanline);
        }
    }
    // ssd1306_show(&disp);
}


void ssd1306_70_40_i2c_handleScanline(uint16_t *line, int scanline) {
    nearestNeighborHandleDownsampling(line, scanline, ssd1306_70_40_i2c_blit);
}

void ssd1306_70_40_i2c_handleFrameEnd(uint8_t frame) {
    ssd1306_show(&disp);
}