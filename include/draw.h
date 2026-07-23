#ifndef DRAW_H
#define DRAW_H
#include "framebuffer.h"

void RB_fill(framebuffer *fb, uint32_t color);

void RB_line2d(framebuffer *fb, vec2i A, vec2i B, uint32_t color);

void RB_tri2d(framebuffer *fb, tri2 tri, uint32_t color);

void RB_fill_tri2d(framebuffer *fb, tri2 tri, uint32_t color);

void RB_tri3d(framebuffer *fb, camera *cam, tri3 tri, uint32_t color);

void RB_fill_tri3d(framebuffer *fb, camera *cam, tri3 tri, uint32_t color);

void RB_draw_mesh3d(framebuffer *fb, camera *cam, mesh3 mesh, vec3 light, uint32_t color);

#endif