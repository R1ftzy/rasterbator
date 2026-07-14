#ifndef VECMATH_H
#define VECMATH_H
#include "types.h"
#define VEC3_TO_VEC4(v) ((vec4){(v).x, (v).y, (v).z, 1.0f})
#define DEG_TO_RAD(x) x * 3.14159f / 180.0f

vec3 vec3Add(vec3 A, vec3 B);

vec3 vec3Sub(vec3 A, vec3 B);

float vec3Dot(vec3 A, vec3 B);

vec3 vecCross(vec3 A, vec3 B);

vec3 vec3Normalize(vec3 v);

vec4 mat4MulVec4(mat4 m, vec4 v);

#endif