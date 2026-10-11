#ifndef VECMATH_H
#define VECMATH_H
#include "types.h"
#define VEC3_TO_VEC4(v) ((vec4){(v).x, (v).y, (v).z, 1.0f})
#define DEG_TO_RAD(x) x * 3.14159f / 180.0f

typedef vec4 quat;

// Returns the sum of two 3D vectors (A + B)
vec3 RB_vec3_add(vec3 A, vec3 B);

// Returns the difference of two 3D vectors (A - B)
vec3 RB_vec3_sub(vec3 A, vec3 B);

// Returns the dot product of two 3D vectors (A . B)
float RB_vec3_dot(vec3 A, vec3 B);

// Returns the cross product of two 3D vectors (A x B)
vec3 RB_vec3_cross(vec3 A, vec3 B);

// Returns the direction of a 3D vector v
vec3 RB_vec3_normalize(vec3 v);

// Returns the product of a 4x4 matrix and a 4D vector
vec4 RB_mat4_mul_vec4(mat4 m, vec4 v);

// Returns the product of two 4x4 matrices
mat4 RB_mat4_mul_mat4(mat4 m, mat4 B);

#endif