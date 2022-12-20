#include "ssd1306_70_40.hpp"
#include "pico/ssd1306.h"

extern "C" {
    void* ssd1306_70_40_initScreen(void) {
        SSD1306* display = new SSD1306(128, 64, spi0, /*baudrate*/ 8000 * 1000, /*mosi*/ 3, /*cs*/ 5, /*sclk*/ 2, /*reset*/ 6, /*dc*/ 7);
        display->init();    

        for(int y = 24; y < 64; y++) {
            for(int x = 28; x < 98; x++) {
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