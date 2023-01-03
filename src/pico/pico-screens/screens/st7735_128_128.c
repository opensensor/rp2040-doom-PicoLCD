#include "pico/stdlib.h"
#include "st7735_128_128.h"

void st7735_128_128_initScreen(void) {

    hagl_hal_init();

    for(uint8_t y = 0; y < 128; y++) {
        // blit(x,y,1,1, data);
        hline(0, y, 128, 0x0000);
    }

    // sleep_ms(3000);

    for(uint8_t y = 0; y < 128; y++) {
        // blit(x,y,1,1, data);
        hline(0, y, 128, 0xffff);
    }

    // sleep_ms(3000);
}

void st7735_128_128_handleFrameStart(uint8_t frame) {
    nearestNeighborHandleFrameStart();
}

void st7735_128_128_blit(uint16_t *downsampled_line, int scanline) {
    for (uint8_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
        uint16_t color = downsampled_line[x];
        color = (((color) << 8) & 0xFF00) | (((color) >> 8) & 0xFF);
        put_pixel(x, scanline, color);
    }
    // blit(0, scanline, 1, DOWNSAMPLED_WIDTH, downsampled_line);
}

void st7735_128_128_handleScanline(uint16_t *line, int scanline) {
    
    // for (uint16_t x = 0; x < SCREENWIDTH; x+=3) {
    //     // I... think I got some counterfeit screens
    //     // hagl_color(0,255,0);
    //     // uint8_t r = line[x] & 0b1111110000000000 >> 10;
    //     // uint8_t b = line[x] & 0b0000001111110000 >> 4;
    //     uint16_t color = line[x];
    //     color = (((color) << 8) & 0xFF00) | (((color) >> 8) & 0xFF);
    //     put_pixel(x/3, scanline/3, color);
    // }
    nearestNeighborHandleDownsampling(line, scanline, st7735_128_128_blit);
}