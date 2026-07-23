#include "types.h"
#include <math.h>

vec3 vec3_add(vec3 A, vec3 B)
{
  vec3 vec = {A.x + B.x, A.y + B.y, A.z + B.z};
  return vec;
}

vec3 vec3_sub(vec3 A, vec3 B)
{
  vec3 vec = {A.x - B.x, A.y - B.y, A.z - B.z};
  return vec;
}

float vec3_dot(vec3 A, vec3 B)
{
  return A.x * B.x + A.y * B.y + A.z * B.z;
}

vec3 vec3_cross(vec3 A, vec3 B)
{
  vec3 vec = {
      A.y * B.z - A.z * B.y,
      A.z * B.x - A.x * B.z,
      A.x * B.y - A.y * B.x};
  return vec;
}

vec3 vec3_normalize(vec3 v)
{
  float mag = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  if (mag == 0)
    return v;
  vec3 n = {v.x / mag, v.y / mag, v.z / mag};
  return n;
}

vec4 mat4_mul_vec4(mat4 m, vec4 v)
{
  vec4 o;
  o.x = v.x * m.m[0][0] + v.y * m.m[0][1] + v.z * m.m[0][2] + v.w * m.m[0][3];
  o.y = v.x * m.m[1][0] + v.y * m.m[1][1] + v.z * m.m[1][2] + v.w * m.m[1][3];
  o.z = v.x * m.m[2][0] + v.y * m.m[2][1] + v.z * m.m[2][2] + v.w * m.m[2][3];
  o.w = v.x * m.m[3][0] + v.y * m.m[3][1] + v.z * m.m[3][2] + v.w * m.m[3][3];
  return o;
}

mat4 mat4_mul_mat4(mat4 m, mat4 B)
{
  mat4 o;
  o.m[0][0] = m.m[0][0] * B.m[0][0] + m.m[0][1] * B.m[1][0] + m.m[0][2] * B.m[2][0] + m.m[0][3] * B.m[3][0];
  o.m[0][1] = m.m[0][0] * B.m[0][1] + m.m[0][1] * B.m[1][1] + m.m[0][2] * B.m[2][1] + m.m[0][3] * B.m[3][1];
  o.m[0][2] = m.m[0][0] * B.m[0][2] + m.m[0][1] * B.m[1][2] + m.m[0][2] * B.m[2][2] + m.m[0][3] * B.m[3][2];
  o.m[0][3] = m.m[0][0] * B.m[0][3] + m.m[0][1] * B.m[1][3] + m.m[0][2] * B.m[2][3] + m.m[0][3] * B.m[3][3];

  o.m[1][0] = m.m[1][0] * B.m[0][0] + m.m[1][1] * B.m[1][0] + m.m[1][2] * B.m[2][0] + m.m[1][3] * B.m[3][0];
  o.m[1][1] = m.m[1][0] * B.m[0][1] + m.m[1][1] * B.m[1][1] + m.m[1][2] * B.m[2][1] + m.m[1][3] * B.m[3][1];
  o.m[1][2] = m.m[1][0] * B.m[0][2] + m.m[1][1] * B.m[1][2] + m.m[1][2] * B.m[2][2] + m.m[1][3] * B.m[3][2];
  o.m[1][3] = m.m[1][0] * B.m[0][3] + m.m[1][1] * B.m[1][3] + m.m[1][2] * B.m[2][3] + m.m[1][3] * B.m[3][3];

  o.m[2][0] = m.m[2][0] * B.m[0][0] + m.m[2][1] * B.m[1][0] + m.m[2][2] * B.m[2][0] + m.m[2][3] * B.m[3][0];
  o.m[2][1] = m.m[2][0] * B.m[0][1] + m.m[2][1] * B.m[1][1] + m.m[2][2] * B.m[2][1] + m.m[2][3] * B.m[3][1];
  o.m[2][2] = m.m[2][0] * B.m[0][2] + m.m[2][1] * B.m[1][2] + m.m[2][2] * B.m[2][2] + m.m[2][3] * B.m[3][2];
  o.m[2][3] = m.m[2][0] * B.m[0][3] + m.m[2][1] * B.m[1][3] + m.m[2][2] * B.m[2][3] + m.m[2][3] * B.m[3][3];

  o.m[3][0] = m.m[3][0] * B.m[0][0] + m.m[3][1] * B.m[1][0] + m.m[3][2] * B.m[2][0] + m.m[3][3] * B.m[3][0];
  o.m[3][1] = m.m[3][0] * B.m[0][1] + m.m[3][1] * B.m[1][1] + m.m[3][2] * B.m[2][1] + m.m[3][3] * B.m[3][1];
  o.m[3][2] = m.m[3][0] * B.m[0][2] + m.m[3][1] * B.m[1][2] + m.m[3][2] * B.m[2][2] + m.m[3][3] * B.m[3][2];
  o.m[3][3] = m.m[3][0] * B.m[0][3] + m.m[3][1] * B.m[1][3] + m.m[3][2] * B.m[2][3] + m.m[3][3] * B.m[3][3];
  return o;
}
