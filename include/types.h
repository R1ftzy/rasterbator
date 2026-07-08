#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>
typedef struct
{
  uint32_t *pixels;
  int height;
  int width;
} framebuffer;

typedef struct
{
  int x, y;
} vec2i;
typedef struct
{
  float x, y;
} vec2;

typedef struct
{
  float x, y, z;
} vec3;

typedef struct
{
  vec2i v[3];
} tri2;

typedef struct
{
  vec3 v[3];
} tri3;

typedef struct
{
  float m[4][4];
} mat4;
#endif