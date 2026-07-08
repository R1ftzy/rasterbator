#ifndef DRAW_H
#define DRAW_H
#include "framebuffer.h"

void fill(framebuffer *fb, uint32_t color);

void line2d(framebuffer *fb, vec2 A, vec2 B, uint32_t color);
#endif