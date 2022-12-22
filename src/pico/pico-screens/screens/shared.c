#include "shared.h"

static uint8_t current_downsampled_row = 0;
static uint16_t downsampled_row[DOWNSAMPLED_WIDTH] = {0}; // I have no idea why I can't do (int)DOWNSAMPLED_WIDTH

#define CEILINGED_DOWNSAMPLING_FACTOR ceiling(DOWNSAMPLING_FACTOR_OUT_OF_100, 100)

uint16_t ceiling(uint16_t dividend,uint16_t divisor) {
    return dividend/divisor + (dividend % divisor != 0);
}

void clearDownsampleBuffers() {
  memset(downsampled_row, 0, sizeof(downsampled_row[0]) * DOWNSAMPLED_WIDTH);
}

// TODO this picks up trash on the very last run - on a [100] array at 98 we'll check 98 99 100 101
uint16_t areaAverageDownsamplePixelGroup(uint16_t *src) {
    uint16_t r_sum = 0, g_sum = 0, b_sum = 0;

    for(uint8_t pixel = 0; pixel < (CEILINGED_DOWNSAMPLING_FACTOR); pixel++) {
        r_sum += ((src[pixel] & 0b1111100000000000) >> 11);
        g_sum += ((src[pixel] & 0b0000011111100000) >> 5);
        b_sum += (src[pixel] & 0b0000000000011111);
    }

    uint16_t downsampled_pixel;
    downsampled_pixel  =   (b_sum / CEILINGED_DOWNSAMPLING_FACTOR)        & 0b0000000000011111;
    downsampled_pixel |= (((g_sum / CEILINGED_DOWNSAMPLING_FACTOR) << 5)  & 0b0000011111100000);
    downsampled_pixel |= (((r_sum / CEILINGED_DOWNSAMPLING_FACTOR) << 11) & 0b1111100000000000);

    return downsampled_pixel;
}

void areaAverageDownsampleLine(uint16_t *src, uint16_t *dest) {
    for (uint16_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
        // Calculate the range of source pixels to average for this destination pixel
        uint16_t start = (uint16_t)(x * DOWNSAMPLING_FACTOR_OUT_OF_100 / 100);
      
        uint16_t downsampled_pixel = areaAverageDownsamplePixelGroup(&src[start]);

        uint16_t temp_column[DOWNSAMPLING_FACTOR_OUT_OF_100 / 100+1] = {downsampled_pixel};

        // uint8_t r = ((downsampled_pixel & 0b1111100000000000) >> 11) ;
        // uint8_t g = ((downsampled_pixel & 0b0000011111100000) >> 5) ;
        // uint8_t b = ( downsampled_pixel & 0b0000000000011111);

        // uint16_t averaged_pixel;
        // averaged_pixel  =   (b * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100)       & 0b0000000000011111;
        // averaged_pixel |= (((g * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100) << 5)  & 0b0000011111100000);
        // averaged_pixel |= (((r * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100) << 11) & 0b1111100000000000);
        
        // exploiting downsampled_pixel. should maybe do this first-class
        dest[x] += areaAverageDownsamplePixelGroup(temp_column);
    }
}

void areaAverageHandleDownsampling(uint16_t *src, int scanline, void (*callback)(uint16_t *, int)) {
    areaAverageDownsampleLine(src, downsampled_row);
    current_downsampled_row++;

    // TODO make it handle whole downsample factors too
    if (current_downsampled_row >= CEILINGED_DOWNSAMPLING_FACTOR) {
        if (CEILINGED_DOWNSAMPLING_FACTOR == DOWNSAMPLING_FACTOR_OUT_OF_100 / 100) {
            // we have no need of revisiting scanlines
            callback(downsampled_row, scanline);
            current_downsampled_row = 0;
            clearDownsampleBuffers();
        } else {
            callback(downsampled_row, scanline-1);
            current_downsampled_row = 1;
            clearDownsampleBuffers();

            // here's that revisit I was talkin about
            areaAverageDownsampleLine(src, downsampled_row);
        }
    }
}





uint16_t nearestNeighborDownsamplePixelGroup(uint16_t *src) {
    return src[0]; // lol
}

void nearestNeighborDownsampleLine(uint16_t *src, uint16_t *dest) {
    for (uint16_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
      // Calculate the range of source pixels to average for this destination pixel
      uint16_t start = (uint16_t)((x * DOWNSAMPLING_FACTOR_OUT_OF_100) / 100);
      
      dest[x] = nearestNeighborDownsamplePixelGroup(&src[start]);
    }
}

void nearestNeighborHandleDownsampling(uint16_t *src, int scanline, void (*callback)(uint16_t *, int)) {
    // this is all we have to do to downsample by x _and_ y
    if (current_downsampled_row == 0) {
        nearestNeighborDownsampleLine(src, downsampled_row);
    }
    current_downsampled_row++;

    if ((current_downsampled_row >= CEILINGED_DOWNSAMPLING_FACTOR) {
        // if we are on a whole number downsampling factor
        if (CEILINGED_DOWNSAMPLING_FACTOR == DOWNSAMPLING_FACTOR_OUT_OF_100 / 100) {
            callback(downsampled_row, scanline);
            current_downsampled_row = 0;
            clearDownsampleBuffers();
        } else {
            // black banding is displayed if we don't do this
            callback(downsampled_row, scanline-1);
            current_downsampled_row = 0;
            clearDownsampleBuffers();
        }
    } 
}