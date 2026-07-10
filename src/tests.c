#include <stdint.h>
#include "types.h"
#include "color.h"
#include "draw.h"
#include "noise.h"

void pink_shit(framebuffer *fb, mesh2 mesh)
{
  uint32_t tint = RGB(207, 159, 255);
  init(fb);
  fractal_fill(fb, tint);

  drawTri2d(fb, mesh.tris[0], RGBA(255, 125, 200, 255));
  triangle_fill(fb, mesh.tris[0], PINK);

  drawTri2d(fb, mesh.tris[1], RGBA(255, 105, 180, 255));
  triangle_fill(fb, mesh.tris[1], RGBA(230, 90, 160, 255));

  drawTri2d(fb, mesh.tris[2], RGBA(255, 105, 180, 255));
  triangle_fill(fb, mesh.tris[2], RGBA(200, 55, 90, 255));
}

void green_shit(framebuffer *fb, mesh2 mesh)
{
  uint32_t tint = RGB(67, 21, 19);
  init(fb);
  fractal_fill(fb, tint);

  drawTri2d(fb, mesh.tris[0], BLACK);
  triangle_fill(fb, mesh.tris[0], RGB(113, 106, 78));

  drawTri2d(fb, mesh.tris[1], BLACK);
  triangle_fill(fb, mesh.tris[1], RGB(44, 68, 51));

  drawTri2d(fb, mesh.tris[2], BLACK);
  triangle_fill(fb, mesh.tris[2], RGB(28, 59, 51));
}

void blue_shit(framebuffer *fb, mesh2 mesh)
{
  uint32_t tint = BLUE;
  init(fb);
  fractal_fill(fb, tint);

  drawTri2d(fb, mesh.tris[0], BLACK);
  triangle_fill(fb, mesh.tris[0], RGB(0, 100, 200));

  drawTri2d(fb, mesh.tris[1], BLACK);
  triangle_fill(fb, mesh.tris[1], RGB(44, 68, 255));

  drawTri2d(fb, mesh.tris[2], BLACK);
  triangle_fill(fb, mesh.tris[2], RGB(0, 59, 180));
}
