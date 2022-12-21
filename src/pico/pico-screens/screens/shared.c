#include "shared.h"

uint16_t ceil(dividend,divisor) {
    return dividend/divisor + (dividend % divisor != 0);
}

uint16_t downsample_pixel_group(uint16_t *src) {
    uint16_t r_sum = 0, g_sum = 0, b_sum = 0;

    for(uint8_t pixel = 0; pixel < (DOWNSAMPLING_FACTOR_OUT_OF_100 / 100); pixel++) {
        r_sum += ((src[pixel] & 0b1111100000000000) >> 11);
        g_sum += ((src[pixel] & 0b0000011111100000) >> 5);
        b_sum += (src[pixel] & 0b0000000000011111);
    }

    uint16_t downsampled_pixel;
    downsampled_pixel  =   (b_sum * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100)        & 0b0000000000011111;
    downsampled_pixel |= (((g_sum * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100) << 5)  & 0b0000011111100000);
    downsampled_pixel |= (((r_sum * 100 / DOWNSAMPLING_FACTOR_OUT_OF_100) << 11) & 0b1111100000000000);

    return downsampled_pixel;
}

void downsample_line(uint16_t *src, uint16_t *dest) {
    for (uint16_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
      // Calculate the range of source pixels to average for this destination pixel
      uint16_t start = (uint16_t)(x * DOWNSAMPLING_FACTOR_OUT_OF_100 / 100);
      
      dest[x] = downsample_pixel_group(&src[start]);
    }
}