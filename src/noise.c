#include "framebuffer.h"
#include "noise.h"
#include <math.h>
#define LERP(a, b, t) ((a) * (1.0f - (t)) + (b) * (t))

void funny_images(framebuffer *fb)
{
  FILE *fp = fopen("image.ppm", "wb");
  fprintf(fp, "P6\n%d %d\n255\n", fb->width, fb->height);
  for (size_t i = 0; i < fb->height * fb->width; i++)
  {
    uint32_t red = (fb->pixels[i] >> 16) & 0xFF;
    uint32_t green = (fb->pixels[i] >> 8) & 0xFF;
    uint32_t blue = fb->pixels[i] & 0xFF;
    uint8_t buffer[3] = {red, green, blue};
    fwrite(buffer, sizeof(uint8_t), 3, fp);
  }
  fclose(fp);
  noise_fill(fb);
  fp = fopen("1dnoise.ppm", "wb");
  fprintf(fp, "P6\n%d %d\n255\n", fb->width, fb->height);
  for (size_t i = 0; i < fb->height * fb->width; i++)
  {
    uint32_t red = (fb->pixels[i] >> 16) & 0xFF;
    uint32_t green = (fb->pixels[i] >> 8) & 0xFF;
    uint32_t blue = fb->pixels[i] & 0xFF;
    uint8_t buffer[3] = {red, green, blue};
    fwrite(buffer, sizeof(uint8_t), 3, fp);
  }
  fclose(fp);
  fractal_fill(fb);
  fp = fopen("frac.ppm", "wb");
  fprintf(fp, "P6\n%d %d\n255\n", fb->width, fb->height);
  for (size_t i = 0; i < fb->height * fb->width; i++)
  {
    uint32_t red = (fb->pixels[i] >> 16) & 0xFF;
    uint32_t green = (fb->pixels[i] >> 8) & 0xFF;
    uint32_t blue = fb->pixels[i] & 0xFF;
    uint8_t buffer[3] = {red, green, blue};
    fwrite(buffer, sizeof(uint8_t), 3, fp);
  }
  fclose(fp);
}

float smoothNoise(float x)
{
  int i = (int)x;
  float f = x - i;
  return LERP(sin(i * 43758.5453f) * 0.5f + 0.5f, sin((i + 1) * 43758.5453f) * 0.5f + 0.5f, f * f * (3.0f - 2.0f * f));
}
float hash2D(int x, int y)
{
  float v = sinf(x * 127.1f + y * 311.7f) * 43758.5453f;
  return v - floorf(v);
}

float noise2D(float x, float y)
{
  int ix = (int)floorf(x);
  int iy = (int)floorf(y);
  float fx = x - ix;
  float fy = y - iy;

  float tx = fx * fx * (3.0f - 2.0f * fx);
  float ty = fy * fy * (3.0f - 2.0f * fy);

  float a = hash2D(ix, iy);
  float b = hash2D(ix + 1, iy);
  float c = hash2D(ix, iy + 1);
  float d = hash2D(ix + 1, iy + 1);

  return a + (b - a) * tx + (c - a) * ty + (a - b - c + d) * tx * ty;
}

float fractal_noise(float x, float y)
{
  float value = 0.0f;
  float amplitude = 0.5f;
  float frequency = 1.0f;
  for (int i = 0; i < 5; i++)
  {
    value += noise2D(x * frequency, y * frequency) * amplitude;
    frequency *= 2.0f;
    amplitude *= 0.5f;
  }
  return value;
}
void noise_fill(framebuffer *fb)
{
  for (int x = 0; x < fb->width * fb->height; x++)
  {
    fb->pixels[x] = color(200 * smoothNoise(x * 0.05f), 220 * smoothNoise(x * 0.05f), 240 * smoothNoise(x * 0.05f), 255);
  }
}

void sin_noise_fill(framebuffer *fb)
{
  for (int x = 0; x < fb->width * fb->height; x++)
  {
    fb->pixels[x] = color(255 * sin(x * 0.0008f), 255 * sin(x * 0.001f), 255 * sin(x * 0.003f), 255);
  }
}

void fractal_fill(framebuffer *fb)
{
  for (size_t x = 0; x < fb->width; x++)
  {
    for (size_t y = 0; y < fb->height; y++)
    {
      uint8_t v = fractal_noise(x * 0.005f, y * 0.005f) * 255;
      set_pixel(fb, x, y, color(v, v, v, 255));
    }
  }
}