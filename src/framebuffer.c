#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "config.h"

void set_pixel(framebuffer *fb, int x, int y, uint32_t color, float depth)
{
  if (x >= 0 && x < fb->width && y >= 0 && y < fb->height)
  {
    if (depth <= fb->depth[x + y * fb->width])
    {
      fb->pixels[x + y * fb->width] = color;
      fb->depth[x + y * fb->width] = depth;
    }
  }
}
void clear_depth(framebuffer *fb)
{
  for (size_t i = 0; i < fb->width * fb->height; i++)
  {
    fb->depth[i] = 1.0f;
  }
}
void clear_framebuffer(framebuffer *fb)
{
  for (size_t i = 0; i < fb->width * fb->height; i++)
  {
    fb->pixels[i] = 0;
  }
  clear_depth(fb);
}
void init(framebuffer *fb)
{
  fb->width = SCREEN_WIDTH;
  fb->height = SCREEN_HEIGHT;
  fb->pixels = malloc(fb->width * fb->height * sizeof(uint32_t));
  memset(fb->pixels, 0, fb->width * fb->height * sizeof(uint32_t));
  fb->depth = malloc(fb->width * fb->height * sizeof(float));
  clear_depth(fb);
}

void render_image(framebuffer *fb)
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

void render_image_depth(framebuffer *fb)
{
  FILE *fp = fopen("depth.ppm", "wb");
  fprintf(fp, "P6\n%d %d\n255\n", fb->width, fb->height);
  for (size_t i = 0; i < fb->height * fb->width; i++)
  {
    float linearDepth = (2.0 * FNEAR * FFAR) / (FFAR + FNEAR - fb->depth[i] * (FFAR - FNEAR));
    uint8_t depth = (linearDepth / 20) * 255;
    uint8_t buffer[3] = {depth, depth, depth};
    fwrite(buffer, sizeof(uint8_t), 3, fp);
  }
  fclose(fp);
}