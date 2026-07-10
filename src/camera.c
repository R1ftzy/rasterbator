#include "types.h"
#include "vecmath.h"
#include "config.h"
#include <math.h>
#define DEG_TO_RAD 3.14159f / 180.0f

void initCam(camera *cam)
{
  cam->near = 0.1f;
  cam->far = 1000.0f;
  cam->fov = 90.0f;
  cam->aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
}

mat4 camProj(camera *cam)
{
  mat4 matProj = {0};
  float FovRad = 1.0f / tanf(cam->fov * 0.5f * DEG_TO_RAD);

  matProj.m[0][0] = FovRad;
  matProj.m[1][1] = cam->aspect * FovRad;
  matProj.m[2][2] = cam->far / (cam->far - cam->near);
  matProj.m[3][2] = (-cam->far * cam->near) / (cam->far - cam->near);
  matProj.m[2][3] = 1.0f;
  matProj.m[3][3] = 0.0f;

  return matProj;
}
