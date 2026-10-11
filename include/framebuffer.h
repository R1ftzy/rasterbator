#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <stdint.h>
#include <stdio.h>
#include "types.h"

extern framebuffer fb;

void RB_set_pixel(framebuffer *fb, int x, int y, uint32_t color, float depth);

void RB_clear_framebuffer(framebuffer *fb, uint32_t color);

void RB_clear_depth(framebuffer *fb);

void RB_init_framebuffer(framebuffer *fb);

void RB_render_image(framebuffer *fb);

void RB_render_image_depth(framebuffer *fb);
#endif