#ifndef NOISE_H
#define NOISE_H
#include "framebuffer.h"
float smoothNoise(float x);
float hash2D(int x, int y);
float noise2D(float x, float y);
float fractal_noise(float x, float y);
void noise_fill(framebuffer *fb);
void sin_noise_fill(framebuffer *fb);
void fractal_fill(framebuffer *fb);
void funny_images(framebuffer *fb);

#endif