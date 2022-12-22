#include "ssd1306_70_40.hpp"
#include "pico/ssd1306.h"
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

extern "C" {


// extern uint16_t nearestNeighborDownsamplePixelGroup(uint16_t *src);
// extern void nearestNeighborHandleDownsampling(uint16_t *src, uint16_t *dest);

    static SSD1306* display;

    void ssd1306_70_40_initScreen(void) {
        display = new SSD1306(128, 64, PICO_DEFAULT_SPI_INSTANCE, /*baudrate*/ 8000 * 1000, /*mosi*/ PICO_DEFAULT_SPI_TX_PIN, /*cs*/ PICO_DEFAULT_SPI_CSN_PIN, /*sclk*/ PICO_DEFAULT_SPI_SCK_PIN, /*reset*/ 21, /*dc*/ 20);
        display->init();    

        // for(int y = 24; y < 64; y++) {
        //     for(int x = 28; x < 98; x+=3) {
        //         display->draw_pixel(x, y, SSD1306_COLOR_ON);        
        //     }
        // }
        
        // display->draw_pixel(0, 0, SSD1306_COLOR_ON);
        // display->draw_pixel(135, 120, SSD1306_COLOR_ON);
        // display->draw_pixel(40, 70, SSD1306_COLOR_ON);

        // display->update();

        // sleep_ms(1000);
        // return display;
    }

    void ssd1306_70_40_handleFrameStart(uint8_t frame) {
        clearDownsampleBuffers();
    }

    SSD1306PixelColor colorToMonochrome(uint16_t pixel) {
        uint8_t r = pixel & 0b1111100000000000 >> 11;
        uint8_t g = pixel & 0b0000011111100000 >> 5;
        uint8_t b = pixel & 0b0000000000011111;

        uint8_t grayscale = (21 * r + 72 * g + 7 * b) / 100;
        // stg ternarys aren't working or something
        if (grayscale > 5) {
            return SSD1306_COLOR_ON;
        }

        return SSD1306_COLOR_OFF;
    }

    void ssd1306_70_40_downsample_y_and_blit(uint16_t* downsampled_line, int scanline) {
        for (uint16_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
            uint16_t downsampled_pixel = downsampled_line[x];
            SSD1306PixelColor color = colorToMonochrome(downsampled_pixel);
            display->draw_pixel(START_X + x, START_Y + scanline * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100, color);
        }
        display->update();
    }


    void ssd1306_70_40_handleScanline(uint16_t *line, int scanline) {
        nearestNeighborHandleDownsampling(line, scanline, ssd1306_70_40_downsample_y_and_blit);
    }

    void ssd1306_70_40_handleFrameEnd(uint8_t frame) {
        display->update();
    }
}