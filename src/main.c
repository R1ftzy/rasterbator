#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "types.h"
#include "framebuffer.h"
#include "noise.h"
#include "draw.h"

int main()
{
  framebuffer fb;
  uint32_t argb = color(255, 255, 255, 255);
  init(&fb);
  fractal_fill(&fb);
  line2d(&fb, (vec2i){100, 100}, (vec2i){500, 100}, color(255, 0, 0, 255));
  line2d(&fb, (vec2i){100, 100}, (vec2i){500, 500}, color(0, 255, 0, 255));
  line2d(&fb, (vec2i){500, 100}, (vec2i){500, 500}, color(255, 255, 0, 255));
  line2d(&fb, (vec2i){100, 100}, (vec2i){150, 600}, color(0, 0, 255, 255));
  line2d(&fb, (vec2i){500, 500}, (vec2i){150, 600}, color(0, 255, 255, 255));
  render(&fb);
}
