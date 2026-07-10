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

  //   tri2 tris[] = {
  //     {{{100, 100}, {700, 100}, {400, 300}}},
  //     {{{100, 100}, {400, 300}, {400, 600}}},
  //     {{{400, 300}, {700, 100}, {400, 600}}},
  // };
  // mesh2 mesh = {
  //     .tris = tris,
  //     .count = sizeof(tris) / sizeof(tris[0])};
  // green_shit(&fb, mesh);
  
  tri3 tris[] = {
      {{{-3.0f, -1.8f, 5.0f}, {0.0f, 1.8f, 4.25f}, {3.0f, -1.8f, 5.0f}}},
      {{{-0.5f, -1.8f, 3.5f}, {0.0f, 1.8f, 4.25f}, {3.0f, -1.8f, 5.0f}}},
      {{{-3.0f, -1.8f, 5.0f}, {0.0f, 1.8f, 4.25f}, {-0.5f, -1.8f, 3.5f}}},
      {{{-3.0f, -1.8f, 5.0f}, {3.0f, -1.8f, 5.0f}, {-0.5f, -1.8f, 3.5f}}}};
  mesh3 tetrahedron = {.tris = tris};
  epic_3D_shit(&fb, &camera, tetrahedron);
  render(&fb);
}
