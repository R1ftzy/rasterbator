#ifndef VECMATH_H
#define VECMATH_H
#include "types.h"

vec3 vec3Add(vec3 A, vec3 B);

vec3 vec3Sub(vec3 A, vec3 B);

float vec3Dot(vec3 A, vec3 B);

vec3 vecCross(vec3 A, vec3 B);

vec3 vec3Normalize(vec3 v);

vec4 mat4MulVec4(mat4 m, vec4 v);

#endif