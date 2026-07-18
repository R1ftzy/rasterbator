#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <stdint.h>
#include <stdio.h>
#include "types.h"

void set_pixel(framebuffer *fb, int x, int y, uint32_t color, float depth);

void clear_framebuffer(framebuffer *fb, uint32_t color);

void clear_depth(framebuffer *fb);

void init(framebuffer *fb);

void render_image(framebuffer *fb);

void render_image_depth(framebuffer *fb);
#endif