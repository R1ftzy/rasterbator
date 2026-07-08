#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

#define WHITE RGBA(255, 255, 255, 255)
#define BLACK RGBA(0, 0, 0, 255)
#define RED RGBA(255, 0, 0, 255)
#define GREEN RGBA(0, 255, 0, 255)
#define BLUE RGBA(0, 0, 255, 255)
#define YELLOW RGBA(255, 255, 0, 255)
#define CYAN RGBA(0, 255, 255, 255)
#define MAGENTA RGBA(255, 0, 255, 255)
#define PINK RGBA(255, 105, 180, 255)

uint32_t RGBA(int r, int g, int b, int a);
uint32_t RGB(int r, int g, int b);
#endif