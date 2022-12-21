#ifndef __SCREEN_SHARED__
#define __SCREEN_SHARED__

#include "pico.h"
#include "i_video.h"


#define DOOM_WIDTH SCREENWIDTH
#define DOOM_HEIGHT SCREENHEIGHT

#define DOWNSAMPLING_FACTOR_OUT_OF_100 300
#define DOWNSAMPLED_WIDTH ((SCREENWIDTH * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100))
#define DOWNSAMPLED_HEIGHT ((SCREENHEIGHT * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100))

uint16_t downsample_pixel_group(uint16_t *src);
void downsample_line(uint16_t *src, uint16_t *dest);

#endif