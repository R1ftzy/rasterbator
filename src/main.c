#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "types.h"
#include "framebuffer.h"
#include "noise.h"
#include "draw.h"
#include "color.h"
#include "tests.h"

int main()
{
  framebuffer fb;
  tri2 tris[] = {
      {{{100, 100}, {700, 100}, {400, 300}}},
      {{{100, 100}, {400, 300}, {400, 600}}},
      {{{400, 300}, {700, 100}, {400, 600}}},
  };
  mesh2 mesh = {
      .tris = tris,
      .count = sizeof(tris) / sizeof(tris[0])};
  green_shit(&fb, mesh);
  render(&fb);
}
