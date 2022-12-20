// DESCRIPTION:
// LED / LCD screen-specific logic

#ifndef __LILYGO_TTGO__
#define __LILYGO_TTGO__

#include "shared.h"

#include "pico.h"
#include "hardware/gpio.h"

// #define LILYGO_TTGO 1

#include <stdlib.h>
#include "pico/st7789.h"

#define MEMORY_WIDTH 320
#define MEMORY_HEIGHT 240

#define LCD_WIDTH 160
#define LCD_HEIGHT 120

void lilygo_ttgo_initScreen(void);
void lilygo_ttgo_handleFrameStart(uint8_t frame);
void lilygo_ttgo_handleScanline(uint16_t *line, int scanline);

#endif