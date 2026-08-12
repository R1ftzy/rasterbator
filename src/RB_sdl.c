#include <SDL3/SDL.h>
#include <config.h>
#include <types.h>
#include <stdint.h>
#include <stdbool.h>
#include <framebuffer.h>
#include <stdlib.h>

extern framebuffer fb;

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static SDL_Event event;

void RB_set_title(const char *title)
{
  SDL_SetWindowTitle(window, title);
}

uint64_t ticksPerSecond, lastTickCount;

uint64_t get_delta_time()
{
  uint64_t currentTickCount = SDL_GetPerformanceCounter();
  uint64_t elapsedTicks = currentTickCount - lastTickCount;
  // Convert to microseconds to not lose precision
  uint64_t elapsedTimeInMicroseconds = (elapsedTicks * 1000000) / ticksPerSecond;
  lastTickCount = currentTickCount;
  return elapsedTimeInMicroseconds;
}
bool is_running()
{
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_EVENT_QUIT)
    {
      SDL_DestroyWindow(window);
      SDL_Quit();
      return false;
    }
  }
  return true;
}
void draw_frame()
{
  SDL_UpdateTexture(
      texture,
      NULL,
      fb.pixels,
      fb.width * sizeof(uint32_t));
  SDL_RenderClear(renderer);
  SDL_RenderTexture(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void RB_create_window()
{
  init_framebuffer(&fb);
  fb.pixels = malloc(fb.width * fb.height * sizeof(uint32_t));
  SDL_Init(SDL_INIT_VIDEO);
  float scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
  window = SDL_CreateWindow(
      "Rasterbator SDL",
      (int)(fb.width * scale),
      (int)(fb.height * scale),
      0);
  renderer = SDL_CreateRenderer(window, NULL);
  texture = SDL_CreateTexture(
      renderer,
      SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STREAMING,
      fb.width,
      fb.height);
  ticksPerSecond = SDL_GetPerformanceFrequency();
  lastTickCount = SDL_GetPerformanceCounter();
}