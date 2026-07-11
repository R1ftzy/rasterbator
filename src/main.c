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
#include "vecmath.h"
#include "camera.h"
#include "config.h"

int main()
{
  framebuffer fb;
  init(&fb);
  camera camera;
  initCam(&camera);
  fractal_fill(&fb, HSV(212, 0.4f, 1.00f));
  vec3 light = {1.0f, -2.0f, 2.0f};

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
  vec3 A = {-1.0f, 1.0f, 3.0f};
  vec3 B = {1.0f, 1.0f, 3.0f};
  vec3 C = {0.0f, -0.8f, 3.0f};
  vec3 D = {0.0f, 0.05f, 1.0f};
  tri3 tris[] = {
      {A, B, D},
      {C, D, B},
      {A, D, C},
      {C, B, A},
  };
  mesh3 tetrahedron = {
      .tris = tris,
      .count = sizeof(tris) / sizeof(tris[0])};
  drawMesh3d(&fb, &camera, tetrahedron, light);
  render(&fb);
  render_depth(&fb);
}
