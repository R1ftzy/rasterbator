#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

uint32_t color(int r, int g, int b, int a)
{
  uint32_t argb = (a << 24) | (r << 16) | (g << 8) | b;
  return argb;
}

void set_pixel(framebuffer *fb, int x, int y, uint32_t color)
{
  fb->pixels[x + y * fb->width] = color;
}

void init(framebuffer *fb)
{
  fb->width = 1280;
  fb->height = 720;
  fb->pixels = malloc(fb->width * fb->height * sizeof(uint32_t));
}

void render(framebuffer *fb)
{
  FILE *fp = fopen("image.ppm", "wb");
  fprintf(fp, "P6\n%d %d\n255\n", fb->width, fb->height);
  for (size_t i = 0; i < fb->height * fb->width; i++)
  {
    uint8_t red = (fb->pixels[i] >> 16) & 0xFF;
    uint8_t green = (fb->pixels[i] >> 8) & 0xFF;
    uint8_t blue = fb->pixels[i] & 0xFF;
    uint8_t buffer[3] = {red, green, blue};
    fwrite(buffer, sizeof(uint8_t), 3, fp);
  }
  fclose(fp);
}