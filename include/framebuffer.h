#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <stdint.h>
#include <stdio.h>
#include "types.h"

void set_pixel(framebuffer *fb, int x, int y, uint32_t color, float depth);

void init(framebuffer *fb);

void render(framebuffer *fb);

#endif