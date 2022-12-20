#include "ssd1306_70_40.hpp"
#include "pico/ssd1306.h"

    // .spi      = PICO_DEFAULT_SPI_INSTANCE,
    // .gpio_din = PICO_DEFAULT_SPI_TX_PIN,
    // .gpio_clk = PICO_DEFAULT_SPI_SCK_PIN,
    // .gpio_cs  = PICO_DEFAULT_SPI_CSN_PIN,
    // .gpio_dc  = 20,
    // .gpio_rst = 21,
    // .gpio_bl  = 22,

extern "C" {
    void* ssd1306_70_40_initScreen(void) {
        SSD1306* display = new SSD1306(128, 64, PICO_DEFAULT_SPI_INSTANCE, /*baudrate*/ 8000 * 1000, /*mosi*/ PICO_DEFAULT_SPI_TX_PIN, /*cs*/ PICO_DEFAULT_SPI_CSN_PIN, /*sclk*/ PICO_DEFAULT_SPI_SCK_PIN, /*reset*/ 21, /*dc*/ 20);
        display->init();    

        for(int y = 24; y < 64; y++) {
            for(int x = 28; x < 98; x+=3) {
                display->draw_pixel(x, y, SSD1306_COLOR_ON);        
            }
        }
        
        // display.draw_pixel(0, 0, SSD1306_COLOR_ON);
        // display.draw_pixel(135, 120, SSD1306_COLOR_ON);
        // display.draw_pixel(40, 70, SSD1306_COLOR_ON);

        display->update();

        sleep_ms(1000);
        return display;
    }
}