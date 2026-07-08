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
} vec2;
#endif