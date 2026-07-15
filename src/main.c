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
  vec3 light = {-1.0f, -1.0f, 2.0f};
  cock_n_balls(&fb, &camera, light);
  render(&fb);
  render_depth(&fb);
}
