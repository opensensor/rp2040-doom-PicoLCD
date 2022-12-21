#include "ssd1306_70_40.hpp"
#include "pico/ssd1306.h"

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

        display->update();

        sleep_ms(1000);
        // return display;
    }

    void ssd1306_70_40_handleFrameStart(uint8_t frame) {
        // display->clear();
    }

    void ssd1306_70_40_handleScanline(uint16_t *line, int scanline) {
        if (scanline % 5 != 0) {
            return;
        }

        for (uint8_t x = 0; x < SCREENWIDTH/5; x++) {
            uint8_t r = line[x*5] & 0b1111100000000000 >> 11;
            uint8_t g = line[x*5] & 0b0000011111100000 >> 5;
            uint8_t b = line[x*5] & 0b0000000000011111;

            uint8_t grayscale = (21 * r + 72 * g + 7 * b) / 100;

            SSD1306PixelColor color;
            if (grayscale > 5) {
                color = SSD1306_COLOR_ON;
            } else {
                color = SSD1306_COLOR_OFF;
            }
            // The pixel should be rendered to monochrome if the grayscale value is less than or equal to 127.
            display->draw_pixel(START_X + x, START_Y + scanline/5, color);
        }
        display->update();
    }

    void ssd1306_70_40_handleFrameEnd(uint8_t frame) {
        display->update();
    }
}