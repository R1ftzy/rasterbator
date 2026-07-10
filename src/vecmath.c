#include "types.h"
#include <math.h>

vec3 vec3Add(vec3 A, vec3 B)
{
  vec3 vec = {A.x + B.x, A.y + B.y, A.z + B.z};
  return vec;
}

vec3 vec3Sub(vec3 A, vec3 B)
{
  vec3 vec = {A.x - B.x, A.y - B.y, A.z - B.z};
  return vec;
}

float vec3Dot(vec3 A, vec3 B)
{
  return A.x * B.x + A.y * B.y + A.z * B.z;
}

vec3 vecCross(vec3 A, vec3 B)
{
  vec3 vec = {
      A.y * B.z - A.z * B.y,
      A.z * B.x - A.x * B.z,
      A.x * B.y - A.y * B.x};
  return vec;
}

vec3 vec3Normalize(vec3 v)
{
  float mag = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  if (mag == 0)
    return v;
  vec3 n = {v.x / mag, v.y / mag, v.z / mag};
  return n;
}

vec4 mat4MulVec4(mat4 m, vec4 v)
{
  vec4 o;
  o.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + v.w*m.m[3][0];
  o.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + v.w*m.m[3][1];
  o.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + v.w*m.m[3][2];
  o.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w*m.m[3][3];
  return o;
}

