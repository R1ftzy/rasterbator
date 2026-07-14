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
#include "trans.h"

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
  moveMesh(&tetrahedron, 0.0, 0.9, 0);
  rotateMesh(&tetrahedron, 90, 0, 0);
  drawMesh3d(&fb, &camera, tetrahedron, light, GREEN);
  mesh3 cock;
  parse_obj("assets/rectangle.obj", &cock);
  moveMesh(&cock, 0, -0.6, 0);
  rotateMesh(&cock, 0, 45, 0);
  drawMesh3d(&fb, &camera, cock, light, PINK);
  mesh3 cube;
  parse_obj("assets/cube.obj", &cube);
  moveMesh(&cube, -1, -1.2, 0);
  drawMesh3d(&fb, &camera, cube, light, RED);
  mesh3 cube_blue;
  parse_obj("assets/cube.obj", &cube_blue);
  moveMesh(&cube_blue, 1, -1.2, 0);
  drawMesh3d(&fb, &camera, cube_blue, light, BLUE);
  render(&fb);
  render_depth(&fb);
}
