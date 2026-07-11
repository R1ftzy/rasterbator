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
#include "obj.h"
int main()
{
  framebuffer fb;
  init(&fb);
  camera camera;
  initCam(&camera);
  fractal_fill(&fb, HSV(340, 0.1f, 1.00f));
  vec3 light = {-1.0f, -1.0f, 2.0f};
  mesh3 tetrahedron;
  parse_obj("assets/tetra.obj", &tetrahedron);
  drawMesh3d(&fb, &camera, tetrahedron, light, GREEN);
  mesh3 cube;
  parse_obj("assets/cube.obj", &cube);
  drawMesh3d(&fb, &camera, cube, light, RED);
  parse_obj("assets/cube_mirror.obj", &cube);
  drawMesh3d(&fb, &camera, cube, light, BLUE);
  render(&fb);
  render_depth(&fb);
}
