/*
right is +X
up is +Y
forward is -Z
*/


#include "types.h"
#include "vecmath.h"
#include "config.h"
#include <math.h>

void init_cam(camera *cam)
{
  cam->eye = (vec3){0, 0, 0};
  cam->up = (vec3){0, 1, 0};
  cam->target = (vec3){0, 0, -1};
  cam->fnear.d = FNEAR;
  cam->fnear.normal = (vec3){0, 0, -1}; 
  cam->ffar.normal = (vec3){0, 0, 1}; 
  cam->ffar.d = FFAR;
  cam->fov = FFOV;
  cam->aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
}

mat4 cam_proj(camera *cam)
{
  mat4 matProj = {0};
  float FovRad = 1.0f / tanf(0.5f * DEG_TO_RAD(cam->fov));

  matProj.m[0][0] = FovRad;
  matProj.m[1][1] = cam->aspect * FovRad;
  matProj.m[2][2] = cam->ffar.d / (cam->ffar.d - cam->fnear.d);
  matProj.m[2][3] = (-cam->ffar.d * cam->fnear.d) / (cam->ffar.d - cam->fnear.d);
  matProj.m[3][2] = 1.0f;
  matProj.m[3][3] = 0.0f;

  return matProj;
}

mat4 look_at_matrix(camera *cam)
{
  vec3 forward = vec3_normalize(vec3_sub(cam->target, cam->eye));
  vec3 right = vec3_normalize(vec3_cross(cam->up, forward));
  vec3 up = vec3_normalize(vec3_cross(forward, right));

  mat4 look = {0};

  look.m[0][0] = right.x;
  look.m[0][1] = right.y;
  look.m[0][2] = right.z;

  look.m[1][0] = up.x;
  look.m[1][1] = up.y;
  look.m[1][2] = up.z;

  look.m[2][0] = forward.x;
  look.m[2][1] = forward.y;
  look.m[2][2] = forward.z;

  look.m[0][3] = -vec3_dot(right, cam->eye);
  look.m[1][3] = -vec3_dot(up, cam->eye);
  look.m[2][3] = -vec3_dot(forward, cam->eye);

  look.m[3][3] = 1;

  return look;
}

mat4 update_view(camera *cam){
  mat4 M = mat4_mul_mat4(cam_proj(cam), look_at_matrix(cam));
  return M;
}