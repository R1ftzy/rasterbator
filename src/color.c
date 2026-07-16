#include <stdint.h>

uint32_t RGBA(int r, int g, int b, int a)
{
  uint32_t argb = (a << 24) | (r << 16) | (g << 8) | b;
  return argb;
}

uint32_t rgb(int r, int g, int b)
{
  int a = 255;
  uint32_t argb = (a << 24) | (r << 16) | (g << 8) | b;
  return argb;
}

uint32_t HSV(float h, float s, float v)
{
  float r, g, b;

  int i = h / 60;
  float f = h / 60 - i;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);

  switch (i % 6)
  {
  case 0:
    r = v, g = t, b = p;
    break;
  case 1:
    r = q, g = v, b = p;
    break;
  case 2:
    r = p, g = v, b = t;
    break;
  case 3:
    r = p, g = q, b = v;
    break;
  case 4:
    r = t, g = p, b = v;
    break;
  case 5:
    r = v, g = p, b = q;
    break;
  }

  uint32_t color = rgb((int)(r * 255), (int)(g * 255), (int)(b * 255));
  return color;
}