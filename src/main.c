#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "types.h"
#include "framebuffer.h"
#include "noise.h"
#include "draw.h"
#include "color.h"

int main()
{
  framebuffer fb;
  uint32_t tint = RGB(67, 21, 19);
  init(&fb);
  fractal_fill(&fb, tint);
  // drawLine2d(&fb, (vec2i){100, 100}, (vec2i){500, 100}, RGBA(255, 0, 0, 255));
  // drawLine2d(&fb, (vec2i){100, 100}, (vec2i){500, 500}, RGBA(0, 255, 0, 255));
  // drawLine2d(&fb, (vec2i){500, 100}, (vec2i){500, 500}, RGBA(255, 255, 0, 255));
  // drawLine2d(&fb, (vec2i){100, 100}, (vec2i){150, 600}, RGBA(0, 0, 255, 255));
  // drawLine2d(&fb, (vec2i){500, 500}, (vec2i){150, 600}, RGBA(0, 255, 255, 255));
  tri2 tri_1 = {
      {{100, 100},
       {700, 100},
       {400, 300}}};
  drawTri2d(&fb, tri_1, BLACK);
  triangle_fill(&fb, tri_1, RGB(113, 106, 78));
  tri2 tri_2 = {
      {{100, 100},
       {400, 300},
       {400, 600}}};
  drawTri2d(&fb, tri_2, BLACK);
  triangle_fill(&fb, tri_2, RGB(44, 68, 51));
  tri2 tri_3 = {
      {{400, 300},
       {700, 100},
       {400, 600}}};
  drawTri2d(&fb, tri_3, BLACK);
  triangle_fill(&fb, tri_3, RGB(28, 59, 51));
  render(&fb);
}
