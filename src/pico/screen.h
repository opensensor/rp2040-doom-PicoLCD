// DESCRIPTION:
// LED / LCD screen-specific logic

#ifndef __I_SCREEN__
#define __I_SCREEN__

#include "i_video.h"

#include "pico.h"
#include "hardware/gpio.h"

// #define LILYGO_TTGO 1


#if ST7789
#include <stdlib.h>
#include "pico/st7789.h"
#elif LILYGO_TTGO
#include <stdlib.h>
#include "pico/st7789.h"
#endif


#if ST7789
#define MEMORY_WIDTH 320
#define MEMORY_HEIGHT 240

#define LCD_WIDTH 160
#define LCD_HEIGHT 120
#elif LILYGO_TTGO

#define MEMORY_WIDTH 320
#define MEMORY_HEIGHT 240

#define LCD_WIDTH 160
#define LCD_HEIGHT 120
#endif

// TODO find wherever these are already stored
#define DOOM_WIDTH SCREENWIDTH
#define DOOM_HEIGHT SCREENHEIGHT

void I_initScreen(void);
void I_handleFrameStart(uint8_t frame);
void I_handleScanline(uint16_t *line, int scanline);

#endif