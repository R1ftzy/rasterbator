#include <stdint.h>
#include "types.h"
#include "color.h"
#include "draw.h"
#include "noise.h"
#include "trans.h"
#include "obj.h"

void pink_shit(framebuffer *fb, mesh2 mesh)
{
  uint32_t tint = rgb(207, 159, 255);
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
  uint32_t tint = rgb(67, 21, 19);
  init(fb);
  fractal_fill(fb, tint);

  drawTri2d(fb, mesh.tris[0], BLACK);
  fillTri2d(fb, mesh.tris[0], rgb(113, 106, 78));

  drawTri2d(fb, mesh.tris[1], BLACK);
  fillTri2d(fb, mesh.tris[1], rgb(44, 68, 51));

  drawTri2d(fb, mesh.tris[2], BLACK);
  fillTri2d(fb, mesh.tris[2], rgb(28, 59, 51));
}

void blue_shit(framebuffer *fb, mesh2 mesh)
{
  uint32_t tint = BLUE;
  init(fb);
  fractal_fill(fb, tint);

  drawTri2d(fb, mesh.tris[0], BLACK);
  fillTri2d(fb, mesh.tris[0], rgb(0, 100, 200));

  drawTri2d(fb, mesh.tris[1], BLACK);
  fillTri2d(fb, mesh.tris[1], rgb(44, 68, 255));

  drawTri2d(fb, mesh.tris[2], BLACK);
  fillTri2d(fb, mesh.tris[2], rgb(0, 59, 180));
}
//   tri3 base[] = {
//       {{{-5.0f, -1.8f, 3.0f}, {-5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 3.0f}}},
//       {{{-5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 3.0f}}}};
//   fillTri3d(&fb, &camera, base[0], HSV(220, 0.4f, 0.6f));
//   fillTri3d(&fb, &camera, base[1], HSV(220, 0.4f, 0.6f));

//   tri3 tris[] = {
//       {{{3.0f, -1.8f, 5.0f}, {0.0f, 1.8f, 4.25f}, {-3.0f, -1.8f, 5.0f}}},
//       {{{-0.5f, -1.8f, 3.5f}, {0.0f, 1.8f, 4.25f}, {3.0f, -1.8f, 5.0f}}},
//       {{{-3.0f, -1.8f, 5.0f}, {0.0f, 1.8f, 4.25f}, {-0.5f, -1.8f, 3.5f}}},
//       {{{-0.5f, -1.8f, 3.5f}, {3.0f, -1.8f, 5.0f}, {-3.0f, -1.8f, 5.0f}}}};
//   mesh3 tetrahedron = {.tris = tris};
//   epic_3D_shit(&fb, &camera, tetrahedron, light);

void epic_3D_shit(framebuffer *fb, camera *camera, mesh3 mesh, vec3 light)
{
  fillTri3d(fb, camera, mesh.tris[0], HSV(0, 0.49f, 0.67f));
  fillTri3d(fb, camera, mesh.tris[1], HSV(90, 0.60f, 0.67f));
  fillTri3d(fb, camera, mesh.tris[3], HSV(210, 0.70f, 0.67f));
}

void cock_n_balls(framebuffer *fb, camera *camera, vec3 light)
{
  fractal_fill(fb, HSV(340, 0.1f, 1.00f));
  tri3 tris[] = {
      {{{-5.0f, -1.8f, 3.0f}, {-5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 3.0f}}},
      {{{-5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 3.0f}}}};
  mesh3 base = {.tris = tris, .count = sizeof(tris) / sizeof(tris[0])};
  drawMesh3d(fb, camera, base, light, ORANGE);
  mesh3 tip;
  parse_obj("assets/tetra.obj", &tip);
  moveMesh(&tip, 0.0, 0.9, 0);
  rotateMeshEuler(&tip, 90, 0, 0);
  drawMesh3d(fb, camera, tip, light, GREEN);
  mesh3 cock;
  parse_obj("assets/rectangle.obj", &cock);
  moveMesh(&cock, 0, -0.6, 0);
  rotateMeshEuler(&cock, 0, 45, 0);
  drawMesh3d(fb, camera, cock, light, PINK);
  mesh3 ball;
  parse_obj("assets/icosphere.obj", &ball);
  scaleMesh(&ball, 0.75, 0.75, 0.75);
  moveMesh(&ball, -1, -1.2, 4);
  drawMesh3d(fb, camera, ball, light, RED);
  mesh3 ball_blue;
  parse_obj("assets/icosphere.obj", &ball_blue);
  scaleMesh(&ball_blue, 0.75, 0.75, 0.75);
  moveMesh(&ball_blue, 1, -1.2, 4);
  drawMesh3d(fb, camera, ball_blue, light, BLUE);
}
