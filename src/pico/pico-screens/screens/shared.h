#ifdef __cplusplus
extern "C" {
#endif

#ifndef __SCREEN_SHARED__
#define __SCREEN_SHARED__

#include "pico.h"
#include "i_video.h"

#define DOOM_WIDTH SCREENWIDTH
#define DOOM_HEIGHT SCREENHEIGHT

// here be some chicanery to avoid floats
#ifndef DOWNSAMPLING_FACTOR_OUT_OF_100
#define DOWNSAMPLING_FACTOR_OUT_OF_100 100
#endif


// Remove the downsampling calculations
#define DOWNSAMPLED_WIDTH SCREENWIDTH
#define DOWNSAMPLED_HEIGHT SCREENHEIGHT

#define DOWNSAMPLING_OFFSET_WIDTH 0
#define DOWNSAMPLING_OFFSET_HEIGHT 0


void clearDownsampleBuffers(void);

uint16_t colorToGreyscale(uint16_t pixel);

void areaAverageHandleDownsampling(uint16_t *src, int scanline, void (*callback)(uint16_t *, int));
void areaAverageHandleFrameStart(void);

void nearestNeighborHandleDownsampling(uint16_t *src, int scanline, void (*callback)(uint16_t *, int));
void nearestNeighborHandleFrameStart(void);

#endif

#ifdef __cplusplus
}
#endif