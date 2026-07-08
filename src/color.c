#include<stdint.h>

uint32_t RGBA(int r, int g, int b, int a)
{
  uint32_t argb = (a << 24) | (r << 16) | (g << 8) | b;
  return argb;
}

uint32_t RGB(int r, int g, int b){
  int a = 255;
  uint32_t argb = (a << 24) | (r << 16) | (g << 8) | b;
  return argb;
}