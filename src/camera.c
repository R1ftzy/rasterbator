#include "types.h"
#include "vecmath.h"

#define DEG_TO_RAD 0.5f / 180.0f * 3.14159f

mat4 camProj(camera *cam)
{
  mat4 matProj;
  float FovRad = 1.0f / tanf(cam->fov * DEG_TO_RAD);

  matProj.m[0][0] = cam->aspect * FovRad;
  matProj.m[1][1] = FovRad;
  matProj.m[2][2] = cam->far / (cam->far - cam->near);
  matProj.m[3][2] = (-cam->far * cam->near) / (cam->far - cam->near);
  matProj.m[2][3] = 1.0f;
  matProj.m[3][3] = 0.0f;

  return matProj;
}
