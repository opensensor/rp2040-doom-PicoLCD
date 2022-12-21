// DESCRIPTION:
// LED / LCD screen-specific logic

#ifndef __ST7789_240_135__
#define __ST7789_240_135__

#include "shared.h"

#include "pico.h"

#include <stdlib.h>
#include "pico/st7789.h"


#define MEMORY_WIDTH 320
#define MEMORY_HEIGHT 240

// #define LCD_WIDTH 160
// #define LCD_HEIGHT 120

void st7789_240_135_initScreen(void);
void st7789_240_135_handleFrameStart(uint8_t frame);
void st7789_240_135_handleScanline(uint16_t *line, int scanline);

#endif