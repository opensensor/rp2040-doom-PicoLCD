#include "screen.h"

#include "screens/lilygo_ttgo.h"
#include "screens/st7789_240_135.h"
#include "screens/ssd1306_70_40.hpp"

#if SSD1306_70_40
static void* ssd1306_70_40;
#endif



void I_initScreen(void) {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

#if ST7789_240_135
    st7789_240_135_initScreen();
#elif LILYGO_TTGO
    lilygo_ttgo_initScreen();
#elif SSD1306_70_40
    ssd1306_70_40 = ssd1306_70_40_initScreen();
#endif
}

void I_handleFrameStart(uint8_t frame) {
    gpio_put(PICO_DEFAULT_LED_PIN, 0);
#if ST7789_240_135
    st7789_240_135_handleFrameStart(frame);
#elif LILYGO_TTGO
    lilygo_ttgo_handleFrameStart(frame);
#endif
}

void I_handleScanline(uint16_t *line, int scanline) {
#if ST7789_240_135
    st7789_240_135_handleScanline(line, scanline);
#elif LILYGO_TTGO
    lilygo_ttgo_handleScanline(line, scanline);
#endif
}

void I_handleFrameEnd(uint8_t frame) {
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
}
