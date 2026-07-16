#include "types.h"
#include "vecmath.h"
#include "config.h"
#include <math.h>

void initCam(camera *cam)
{
  cam->position = (vec3){0, 0, 0};
  cam->fnear = FNEAR;
  cam->ffar = FFAR;
  cam->fov = FFOV;
  cam->aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
}

mat4 camProj(camera *cam)
{
  mat4 matProj = {0};
  float FovRad = 1.0f / tanf(0.5f * DEG_TO_RAD(cam->fov));

  matProj.m[0][0] = FovRad;
  matProj.m[1][1] = cam->aspect * FovRad;
  matProj.m[2][2] = cam->ffar / (cam->ffar - cam->fnear);
  matProj.m[2][3] = (-cam->ffar * cam->fnear) / (cam->ffar - cam->fnear);
  matProj.m[3][2] = 1.0f;
  matProj.m[3][3] = 0.0f;

  return matProj;
}
