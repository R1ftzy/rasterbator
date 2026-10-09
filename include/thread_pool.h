#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <SDL3/SDL.h>
#include "config.h"
#include "draw.h"
typedef struct
{
  SDL_Thread *threads[THREAD_COUNT];
  mt_mesh_args args[THREAD_COUNT];

  SDL_Mutex *mutex;
  SDL_Condition *work_available;
  SDL_Condition *work_done;

  int pending_workers;
  unsigned int generation;
  bool shutdown;
} render_pool;

bool rb_pool_init(render_pool *pool);
void rb_pool_render(render_pool *pool, framebuffer *fb, camera *cam, mesh3 **meshes, int mesh_count, vec3 light);
void rb_pool_destroy(render_pool *pool);

#endif