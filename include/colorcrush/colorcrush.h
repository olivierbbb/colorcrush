#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct ccrush_FlatImg {
    uint32_t width;
    uint32_t height;
    uint8_t *data;
} ccrush_FlatImg;

typedef struct ccrush_IndexedImg {
    uint32_t width;
    uint32_t height;
    unsigned int colors_count;
    uint8_t *palette;
    uint8_t *data;
} ccrush_IndexedImg;

void ccrush_flat_img_init(ccrush_FlatImg *img, uint32_t width, uint32_t height);
void ccrush_flat_img_clear(ccrush_FlatImg *img);

void ccrush_indexed_img_init(ccrush_IndexedImg *indexed_img, uint32_t width, uint32_t height, unsigned int colors_count);
void ccrush_indexed_img_clear(ccrush_IndexedImg *img);

/**
Quantize colors of true color @p flat_img in a new @p indexed_img.
@p max_colors_count: maximum number that the quantized image may contain, ie maximum size of its palette.
It makes sense to set this to a power of 2.
@p max_octree_depth: maximum depth of the octree. Must be between 1 and 8. If @p param max_colors_counts is
not too low, lowering this value may speed up the quantization process without altering the output's quality.
@p use_dither: if true, apply error-correction dithering. The process will be drasticly slowed down but
depending on the image, the visual result may be greatly improved.
@p indexed_img must be uninitialized.
*/
void ccrush_img_quantize(
    ccrush_FlatImg *flat_img,
    unsigned int max_colors_count,
    unsigned int max_octree_depth,
    bool use_dither,
    ccrush_IndexedImg *indexed_img);