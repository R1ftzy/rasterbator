#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <stdint.h>
#include <stdio.h>
#include "types.h"

extern framebuffer fb;


// Sets a color and depth value at x, y
void RB_set_pixel(framebuffer *fb, int x, int y, uint32_t color, float depth);

// Sets all pixels to depth = 1.0f
void RB_clear_framebuffer(framebuffer *fb, uint32_t color);

// Sets all pixels to a specified color and resets the depth
void RB_clear_depth(framebuffer *fb);

// Initializes the framebuffer
void RB_init_framebuffer(framebuffer *fb);

// Saves current framebuffer in a ppm image
void RB_render_image(framebuffer *fb);

// Saves current framebuffer depth information in a ppm image
void RB_render_image_depth(framebuffer *fb);
#endif