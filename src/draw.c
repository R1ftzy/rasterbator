#include <stdbool.h>
#include "framebuffer.h"
#include <stdlib.h>
#include "vecmath.h"
#include "camera.h"
#include "config.h"
#include "types.h"
#include "color.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define LERP(a, b, t) ((a) * (1.0f - (t)) + (b) * (t))

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

void drawLine3d(framebuffer *fb, vec2i A, vec2i B, uint32_t color, float d0, float d1)
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
  int i = 0;
  int steps = MAX((x1 - x0), (y1 - y0));
  while (1)
  {
    float t = (steps > 0) ? (float)i / (float)steps : 0.0f;
    i++;
    float depth = LERP(d0, d1, t);
    set_pixel(fb, x0, y0, color, depth);
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

void fillTri2d(framebuffer *fb, tri2 tri, uint32_t color)
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

void drawTri3d(framebuffer *fb, camera *cam, tri3 tri, uint32_t color)
{
  mat4 matProj = camProj(cam);
  vec4 v0 = VEC3_TO_VEC4(tri.v[0]);
  vec4 v1 = VEC3_TO_VEC4(tri.v[1]);
  vec4 v2 = VEC3_TO_VEC4(tri.v[2]);

  vec4 o0 = mat4MulVec4(matProj, v0);
  vec4 o1 = mat4MulVec4(matProj, v1);
  vec4 o2 = mat4MulVec4(matProj, v2);

  printf("%f %f %f\n", o0.x, o0.y, o0.w);
  printf("%f %f %f\n", o1.x, o1.y, o1.w);
  printf("%f %f %f\n", o2.x, o2.y, o2.w);

  o0.x /= o0.w;
  o0.y /= o0.w;
  o0.z /= o0.w;

  o1.x /= o1.w;
  o1.y /= o1.w;
  o1.z /= o1.w;

  o2.x /= o2.w;
  o2.y /= o2.w;
  o2.z /= o2.w;

  vec2i vi0 = {(int)((o0.x + 1.0f) * 0.5f * SCREEN_WIDTH), (int)((1.0f - o0.y) * 0.5f * SCREEN_HEIGHT)};
  vec2i vi1 = {(int)((o1.x + 1.0f) * 0.5f * SCREEN_WIDTH), (int)((1.0f - o1.y) * 0.5f * SCREEN_HEIGHT)};
  vec2i vi2 = {(int)((o2.x + 1.0f) * 0.5f * SCREEN_WIDTH), (int)((1.0f - o2.y) * 0.5f * SCREEN_HEIGHT)};
  printf("%d %d\n", vi0.x, vi0.y);
  printf("%d %d\n", vi1.x, vi1.y);
  printf("%d %d\n", vi2.x, vi2.y);
  drawLine3d(fb, vi0, vi1, color, o0.z, o1.z);
  drawLine3d(fb, vi1, vi2, color, o1.z, o2.z);
  drawLine3d(fb, vi2, vi0, color, o2.z, o0.z);
}

void fillTri3d(framebuffer *fb, camera *cam, tri3 tri, uint32_t color)
{
  printf("%f, %f, %f \n", tri.v[0].x, tri.v[0].y, tri.v[0].z);
  printf("%f, %f, %f \n", tri.v[1].x, tri.v[1].y, tri.v[1].z);
  printf("%f, %f, %f \n", tri.v[2].x, tri.v[2].y, tri.v[2].z);
  mat4 matProj = camProj(cam);
  vec4 v0 = VEC3_TO_VEC4(tri.v[0]);
  vec4 v1 = VEC3_TO_VEC4(tri.v[1]);
  vec4 v2 = VEC3_TO_VEC4(tri.v[2]);

  vec4 o0 = mat4MulVec4(matProj, v0);
  vec4 o1 = mat4MulVec4(matProj, v1);
  vec4 o2 = mat4MulVec4(matProj, v2);

  printf("%f %f %f\n", o0.x, o0.y, o0.w);
  printf("%f %f %f\n", o1.x, o1.y, o1.w);
  printf("%f %f %f\n", o2.x, o2.y, o2.w);

  if (o0.w < cam->fnear || o1.w < cam->fnear || o2.w < cam->fnear){
    printf("\nToo close too cam\n");
    return;
  }

  o0.x /= o0.w;
  o0.y /= o0.w;
  o0.z /= o0.w;

  o1.x /= o1.w;
  o1.y /= o1.w;
  o1.z /= o1.w;

  o2.x /= o2.w;
  o2.y /= o2.w;
  o2.z /= o2.w;

  vec2i vi0 = {(int)((o0.x + 1.0f) * 0.5f * SCREEN_WIDTH), (int)((1.0f - o0.y) * 0.5f * SCREEN_HEIGHT)};
  vec2i vi1 = {(int)((o1.x + 1.0f) * 0.5f * SCREEN_WIDTH), (int)((1.0f - o1.y) * 0.5f * SCREEN_HEIGHT)};
  vec2i vi2 = {(int)((o2.x + 1.0f) * 0.5f * SCREEN_WIDTH), (int)((1.0f - o2.y) * 0.5f * SCREEN_HEIGHT)};
  printf("%d %d\n", vi0.x, vi0.y);
  printf("%d %d\n", vi1.x, vi1.y);
  printf("%d %d\n", vi2.x, vi2.y);
  tri2 tri2d = {vi0, vi1, vi2};

  // Finds the bounding box with all candidate pixels
  int x_min = MIN(MIN(tri2d.v[0].x, tri2d.v[1].x), tri2d.v[2].x);
  int y_min = MIN(MIN(tri2d.v[0].y, tri2d.v[1].y), tri2d.v[2].y);
  int x_max = MAX(MAX(tri2d.v[0].x, tri2d.v[1].x), tri2d.v[2].x);
  int y_max = MAX(MAX(tri2d.v[0].y, tri2d.v[1].y), tri2d.v[2].y);
  // Compute the constant delta_s that will be used for the horizontal and vertical steps
  int delta_w0_col = (tri2d.v[1].y - tri2d.v[2].y);
  int delta_w1_col = (tri2d.v[2].y - tri2d.v[0].y);
  int delta_w2_col = (tri2d.v[0].y - tri2d.v[1].y);
  int delta_w0_row = (tri2d.v[2].x - tri2d.v[1].x);
  int delta_w1_row = (tri2d.v[0].x - tri2d.v[2].x);
  int delta_w2_row = (tri2d.v[1].x - tri2d.v[0].x);

  // Rasterization fill convention (top-left rule)
  int bias0 = is_top_left(&tri2d.v[1], &tri2d.v[2]) ? 0 : -1;
  int bias1 = is_top_left(&tri2d.v[2], &tri2d.v[0]) ? 0 : -1;
  int bias2 = is_top_left(&tri2d.v[0], &tri2d.v[1]) ? 0 : -1;

  // Compute the edge functions for the fist (top-left) point
  vec2i p0 = {x_min, y_min};
  int w0_row = edge_cross(&tri2d.v[1], &tri2d.v[2], &p0) + bias0;
  int w1_row = edge_cross(&tri2d.v[2], &tri2d.v[0], &p0) + bias1;
  int w2_row = edge_cross(&tri2d.v[0], &tri2d.v[1], &p0) + bias2;
  // Loop all candidate pixels inside the bounding box
  for (int y = y_min; y <= y_max; y++)
  {
    int w0 = w0_row;
    int w1 = w1_row;
    int w2 = w2_row;
    for (int x = x_min; x <= x_max; x++)
    {
      float depth = (w0 * o0.z + w1 * o1.z + w2 * o2.z) / (w0 + w1 + w2);
      bool is_inside = w0 >= 0 && w1 >= 0 && w2 >= 0;
      if (is_inside)
      {
        set_pixel(fb, x, y, color, depth);
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

void drawMesh3d(framebuffer *fb, camera *cam, mesh3 mesh, vec3 light, uint32_t color)
{
  for (size_t i = 0; i < mesh.count; i++)
  {
    vec3 normal = vec3Normalize(vecCross(vec3Sub(mesh.tris[i].v[1], mesh.tris[i].v[0]), vec3Sub(mesh.tris[i].v[2], mesh.tris[i].v[0])));
    vec3 los = vec3Sub(cam->position, mesh.tris[i].v[0]);
    printf("normal: %.2f %.2f %.2f\n", normal.x, normal.y, normal.z);
    if (vec3Dot(normal, los) <= 0)
      continue;
    vec3 face_centre = vec3Add(vec3Add(mesh.tris[i].v[0], mesh.tris[i].v[1]), mesh.tris[i].v[2]);
    vec3 light_dir = vec3Sub(light, face_centre);
    float intensity = vec3Dot(normal, vec3Normalize(light_dir));
    printf("light %f\n", intensity);
    intensity = (intensity < 0) ? 0.0f : intensity;
    printf("light %f\n", intensity);
    uint8_t red = (color >> 16) & 0xFF;
    uint8_t green = (color >> 8) & 0xFF;
    uint8_t blue = color & 0xFF;
    fillTri3d(fb, cam, mesh.tris[i], rgb(red * intensity, green * intensity, blue * intensity));
  }
}
