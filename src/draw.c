#include <stdbool.h>
#include "framebuffer.h"
#include "stdlib.h"
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void fill(framebuffer *fb, uint32_t color)
{
  for (int x = 0; x < fb->width * fb->height; x++)
  {
    fb->pixels[x] = color;
  }
}

void drawLine2d(framebuffer *fb, vec2i A, vec2i B, uint32_t color)
{
  int x0, x1, y0, y1;
  x0 = A.x;
  x1 = B.x;
  y0 = A.y;
  y1 = B.y;
  int dx = abs(x1 - x0);
  int sx = (x0 < x1) ? 1 : -1;
  int dy = -abs(y1 - y0);
  int sy = (y0 < y1) ? 1 : -1;
  int error = dx + dy;
  while (1)
  {
    set_pixel(fb, x0, y0, color, 0.0f);
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

void drawTri2d(framebuffer *fb, tri2 tri, uint32_t color)
{
  drawLine2d(fb, tri.v[0], tri.v[1], color);
  drawLine2d(fb, tri.v[0], tri.v[2], color);
  drawLine2d(fb, tri.v[1], tri.v[2], color);
}

bool is_top_left(vec2i *start, vec2i *end)
{
  vec2i edge = {end->x - start->x, end->y - start->y};
  bool is_top_edge = edge.y == 0 && edge.x > 0;
  bool is_left_edge = edge.y < 0;
  return is_left_edge || is_top_edge;
}

int edge_cross(vec2i *a, vec2i *b, vec2i *p)
{
  vec2i ab = {b->x - a->x, b->y - a->y};
  vec2i ap = {p->x - a->x, p->y - a->y};
  return ab.x * ap.y - ab.y * ap.x;
}

void triangle_fill(framebuffer *fb, tri2 tri, uint32_t color)
{
  // Finds the bounding box with all candidate pixels
  int x_min = MIN(MIN(tri.v[0].x, tri.v[1].x), tri.v[2].x);
  int y_min = MIN(MIN(tri.v[0].y, tri.v[1].y), tri.v[2].y);
  int x_max = MAX(MAX(tri.v[0].x, tri.v[1].x), tri.v[2].x);
  int y_max = MAX(MAX(tri.v[0].y, tri.v[1].y), tri.v[2].y);
  // Compute the constant delta_s that will be used for the horizontal and vertical steps
  int delta_w0_col = (tri.v[1].y - tri.v[2].y);
  int delta_w1_col = (tri.v[2].y - tri.v[0].y);
  int delta_w2_col = (tri.v[0].y - tri.v[1].y);
  int delta_w0_row = (tri.v[2].x - tri.v[1].x);
  int delta_w1_row = (tri.v[0].x - tri.v[2].x);
  int delta_w2_row = (tri.v[1].x - tri.v[0].x);

  // Rasterization fill convention (top-left rule)
  int bias0 = is_top_left(&tri.v[1], &tri.v[2]) ? 0 : -1;
  int bias1 = is_top_left(&tri.v[2], &tri.v[0]) ? 0 : -1;
  int bias2 = is_top_left(&tri.v[0], &tri.v[1]) ? 0 : -1;

  // Compute the edge functions for the fist (top-left) point
  vec2i p0 = {x_min, y_min};
  int w0_row = edge_cross(&tri.v[1], &tri.v[2], &p0) + bias0;
  int w1_row = edge_cross(&tri.v[2], &tri.v[0], &p0) + bias1;
  int w2_row = edge_cross(&tri.v[0], &tri.v[1], &p0) + bias2;
  // Loop all candidate pixels inside the bounding box
  for (int y = y_min; y <= y_max; y++)
  {
    int w0 = w0_row;
    int w1 = w1_row;
    int w2 = w2_row;
    for (int x = x_min; x <= x_max; x++)
    {
      bool is_inside = w0 >= 0 && w1 >= 0 && w2 >= 0;
      if (is_inside)
      {
        set_pixel(fb, x, y, color, 0.0f);
      }
      w0 += delta_w0_col;
      w1 += delta_w1_col;
      w2 += delta_w2_col;
    }
    w0_row += delta_w0_row;
    w1_row += delta_w1_row;
    w2_row += delta_w2_row;
  }
}
