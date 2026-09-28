#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>

typedef struct
{
  uint32_t *pixels;
  float *depth;
  int height;
  int width;
} framebuffer;

typedef struct
{
  int x, y;
} vec2i;

typedef struct
{
  float u, v;
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
  float x, y, z, w;
} vec4;

typedef struct
{
  vec3 v[3];
} tri3;

typedef struct
{
  float m[4][4];
} mat4;

typedef struct
{
  tri2 *tris;
  size_t count;
} mesh2;

typedef struct
{
  tri3 *tris;
  size_t count;
  uint32_t color;
} mesh3;

typedef struct  
{
  vec3 normal;
  float d;
} plane;

typedef struct
{
  vec3 eye;
  vec3 target;
  vec3 up;

  float fov;
  plane fnear;
  plane ffar;
  plane left;
  plane right;
  plane bottom;
  plane top;

  float aspect;
} camera;

#endif