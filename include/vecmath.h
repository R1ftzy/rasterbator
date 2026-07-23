#ifndef VECMATH_H
#define VECMATH_H
#include "types.h"
#define VEC3_TO_VEC4(v) ((vec4){(v).x, (v).y, (v).z, 1.0f})
#define DEG_TO_RAD(x) x * 3.14159f / 180.0f

typedef vec4 quat;

vec3 vec3_add(vec3 A, vec3 B);

vec3 vec3_sub(vec3 A, vec3 B);

float vec3_dot(vec3 A, vec3 B);

vec3 vec3_cross(vec3 A, vec3 B);

vec3 vec3_normalize(vec3 v);

vec4 mat4_mul_vec4(mat4 m, vec4 v);

#endif