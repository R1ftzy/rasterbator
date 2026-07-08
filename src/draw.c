#include "framebuffer.h"
#include "stdlib.h"

void fill(framebuffer *fb, uint32_t color)
{
  for (int x = 0; x < fb->width * fb->height; x++)
  {
    fb->pixels[x] = color;
  }
}

void line2d(framebuffer *fb, vec2 A, vec2 B, uint32_t color)
{
  int x0, x1, y0, y1;
  x0 = B.x;
  x1 = A.x;
  y0 = B.y;
  y1 = A.y;
  int dx = abs(x1 - x0);
  int sx = (x0 < x1) ? 1 : -1;
  int dy = -abs(y1 - y0);
  int sy = (y0 < y1) ? 1 : -1;
  int error = dx + dy;
  while (1)
  {
    set_pixel(fb, x0, y0, color);
    int e2 = 2 * error;
    if (e2 >= dy)
    {
      if (x0 == x1)
        break;
      error += dy;
      x0 += sx;
    }
    if (e2 <= dx)
    {
      if (y0 == y1)
        break;
      error += dx;
      y0 += sy;
    }
  }
}
