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
  fillTri2d(fb, mesh.tris[0], PINK);

  drawTri2d(fb, mesh.tris[1], RGBA(255, 105, 180, 255));
  fillTri2d(fb, mesh.tris[1], RGBA(230, 90, 160, 255));

  drawTri2d(fb, mesh.tris[2], RGBA(255, 105, 180, 255));
  fillTri2d(fb, mesh.tris[2], RGBA(200, 55, 90, 255));
}
//   tri2 tris[] = {
//     {{{100, 100}, {700, 100}, {400, 300}}},
//     {{{100, 100}, {400, 300}, {400, 600}}},
//     {{{400, 300}, {700, 100}, {400, 600}}},
// };
// mesh2 mesh = {
//     .tris = tris,
//     .count = sizeof(tris) / sizeof(tris[0])};
// green_shit(&fb, mesh);
void green_shit(framebuffer *fb, mesh2 mesh)
{
  uint32_t tint = RGB(67, 21, 19);
  init(fb);
  fractal_fill(fb, tint);

  drawTri2d(fb, mesh.tris[0], BLACK);
  fillTri2d(fb, mesh.tris[0], RGB(113, 106, 78));

  drawTri2d(fb, mesh.tris[1], BLACK);
  fillTri2d(fb, mesh.tris[1], RGB(44, 68, 51));

  drawTri2d(fb, mesh.tris[2], BLACK);
  fillTri2d(fb, mesh.tris[2], RGB(28, 59, 51));
}

void blue_shit(framebuffer *fb, mesh2 mesh)
{
  uint32_t tint = BLUE;
  init(fb);
  fractal_fill(fb, tint);

  drawTri2d(fb, mesh.tris[0], BLACK);
  fillTri2d(fb, mesh.tris[0], RGB(0, 100, 200));

  drawTri2d(fb, mesh.tris[1], BLACK);
  fillTri2d(fb, mesh.tris[1], RGB(44, 68, 255));

  drawTri2d(fb, mesh.tris[2], BLACK);
  fillTri2d(fb, mesh.tris[2], RGB(0, 59, 180));
}

void epic_3D_shit(framebuffer *fb, camera *camera, mesh3 mesh, vec3 light)
{
  fillTri3d(fb, camera, mesh.tris[0], HSV(0, 0.49f, 0.67f));
  fillTri3d(fb, camera, mesh.tris[1], HSV(90, 0.60f, 0.67f));
  fillTri3d(fb, camera, mesh.tris[3], HSV(210, 0.70f, 0.67f));
}
