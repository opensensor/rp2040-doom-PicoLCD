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
#define DOWNSAMPLING_FACTOR_OUT_OF_100 137
#define DOWNSAMPLED_WIDTH ((SCREENWIDTH * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100))
#define DOWNSAMPLED_HEIGHT ((SCREENHEIGHT * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100))

void clearDownsampleBuffers(void);

uint16_t areaAverageDownsamplePixelGroup(uint16_t *src);
void areaAverageHandleDownsampling(uint16_t *src, int scanline, void (*callback)(uint16_t *, int));

uint16_t nearestNeighborDownsamplePixelGroup(uint16_t *src);
void nearestNeighborHandleDownsampling(uint16_t *src, int scanline, void (*callback)(uint16_t *, int));

#endif

#ifdef __cplusplus
}
#endif