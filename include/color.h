#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

#define WHITE rgba(255, 255, 255, 255)
#define BLACK rgba(0, 0, 0, 255)
#define RED rgba(255, 0, 0, 255)
#define GREEN rgba(0, 255, 0, 255)
#define BLUE rgba(0, 0, 255, 255)
#define YELLOW rgba(255, 255, 0, 255)
#define CYAN rgba(0, 255, 255, 255)
#define MAGENTA rgba(255, 0, 255, 255)
#define PINK rgba(255, 105, 180, 255)
#define ORANGE rgba(255, 165, 0, 255)
#define PURPLE rgba(128, 0, 128, 255)
#define TEAL rgba(0, 128, 128, 255)
#define LIME rgba(50, 205, 50, 255)
#define CORAL rgba(255, 127, 80, 255)

uint32_t rgba(int r, int g, int b, int a);
uint32_t rgb(int r, int g, int b);
uint32_t HSV(float h, float s, float v);
#endif