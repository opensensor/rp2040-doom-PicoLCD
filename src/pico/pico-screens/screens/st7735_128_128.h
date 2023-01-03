// DESCRIPTION:
// LED / LCD screen-specific logic

#ifndef __ST7735_128_128__
#define __ST7735_128_128__

#include "shared.h"

#include "pico.h"

#include <stdlib.h>
#include "hagl_hal.h"

#undef DOWNSAMPLING_FACTOR_OUT_OF_100
#define DOWNSAMPLING_FACTOR_OUT_OF_100 200

#define SCREEN_WIDTH_OFFSET ((LCD_WIDTH - (SCREENWIDTH * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100)) / 2)


void st7735_128_128_initScreen(void);
void st7735_128_128_handleFrameStart(uint8_t frame);
void st7735_128_128_handleScanline(uint16_t *line, int scanline);

#endif