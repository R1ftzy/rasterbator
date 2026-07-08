#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <stdint.h>
#include <stdio.h>
#include "types.h"

uint32_t color(int r, int g, int b, int a);

void set_pixel(framebuffer *fb, int x, int y, uint32_t color);

void init(framebuffer *fb);

void render(framebuffer *fb);

#endif