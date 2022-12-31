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

static uint8_t buf[SSD1306_BUF_LEN];

static struct render_area frame_area = {
    start_col: 0,
    end_col : SSD1306_WIDTH - 1,
    start_page : 0,
    end_page : SSD1306_NUM_PAGES - 1
};

void calc_render_area_buflen(struct render_area *area) {
    // calculate how long the flattened buffer will be for a render area
    area->buflen = (area->end_col - area->start_col + 1) * (area->end_page - area->start_page + 1);
}

// TODO move this to the screen library
void ssd1306_70_40_i2c_clearScreen(void) {
    memset(buf, 0, SSD1306_BUF_LEN);
}

void ssd1306_70_40_i2c_initScreen(void) {

    bi_decl(bi_2pins_with_func(22, 23, GPIO_FUNC_I2C));
    bi_decl(bi_program_description("SSD1306 OLED driver I2C example for the Raspberry Pi Pico"));
    // I2C is "open drain", pull ups to keep signal high when no data is being
    // sent
    i2c_init(i2c1, SSD1306_I2C_CLK * 1000);
    gpio_set_function(22, GPIO_FUNC_I2C);
    gpio_set_function(23, GPIO_FUNC_I2C);
    gpio_pull_up(22);
    gpio_pull_up(23);

    // run through the complete initialization process
    SSD1306_init();

    calc_render_area_buflen(&frame_area);
    ssd1306_70_40_i2c_clearScreen();
    SSD1306_i2c_render(buf, &frame_area);

    // SSD1306_send_cmd(SSD1306_SET_ALL_OFF);    // Set all pixels on
}

void ssd1306_70_40_i2c_handleFrameStart(uint8_t frame) {
    nearestNeighborHandleFrameStart();
    ssd1306_70_40_i2c_clearScreen();
}

void ssd1306_70_40_i2c_blit(uint16_t* downsampled_line, int scanline) {
    // this converts the line to "monochrome" greyscale
    // ditherDownsampledLine(downsampled_line);
    for (uint16_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
        uint16_t downsampled_pixel = downsampled_line[x];
        
        // comment out if using dithering
        downsampled_pixel = colorToGreyscale(downsampled_pixel);
        SSD1306_setPixel(buf, START_X + x, START_Y + scanline, downsampled_pixel > 127);
    }
}


void ssd1306_70_40_i2c_handleScanline(uint16_t *line, int scanline) {
    nearestNeighborHandleDownsampling(line, scanline, ssd1306_70_40_i2c_blit);
}

void ssd1306_70_40_i2c_handleFrameEnd(uint8_t frame) {
    SSD1306_i2c_render(buf, &frame_area);
}