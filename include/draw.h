#ifndef DRAW_H
#define DRAW_H
#include "framebuffer.h"

void fill(framebuffer *fb, uint32_t color);

void drawLine2d(framebuffer *fb, vec2i A, vec2i B, uint32_t color);

void drawTri2d(framebuffer *fb, tri2 tri, uint32_t color);

void fillTri2d(framebuffer *fb, tri2 tri, uint32_t color);

void drawTri3d(framebuffer *fb, camera *cam, tri3 tri, uint32_t color);

void fillTri3d(framebuffer *fb, camera *cam, tri3 tri, uint32_t color);

#endif