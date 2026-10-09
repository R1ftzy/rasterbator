#include "thread_pool.h"

bool rb_pool_init(render_pool *pool)
{
  pool->mutex = SDL_CreateMutex();
  pool->work_available = SDL_CreateCondition();
  pool->work_done = SDL_CreateCondition();

  if (!pool->mutex || !pool->work_available || !pool->work_done)
  {
    return false;
  }
  for (int i = 0; i < THREAD_COUNT; i++)
  {
    pool->threads[i] = SDL_CreateThread(
        render_worker,
        "RenderWorker",
        &pool->args[i]);
    if (!pool->threads[i])
    {
      rb_pool_destroy(pool);
      return false;
    }
  }
  return true;
}
void rb_pool_destroy(render_pool *pool)
{
}

void rb_pool_render(render_pool *pool, framebuffer *fb, camera *cam, mesh3 **meshes, int mesh_count, vec3 light)
{
  int band_height = fb->height / THREAD_COUNT;

  for (int i = 0; i < THREAD_COUNT; i++)
  {
    pool->args[i].fb = fb;
    pool->args[i].cam = cam;
    pool->args[i].meshes = meshes;
    pool->args[i].mesh_count = mesh_count;
    pool->args[i].light = light;

    pool->args[i].y_min = i * band_height;
    pool->args[i].y_max = (i == THREAD_COUNT - 1)
                              ? fb->height - 1
                              : (i + 1) * band_height - 1;

    pool->threads[i] = SDL_CreateThread(
        render_worker,
        "RenderWorker",
        &pool->args[i]);
  }

  for (int i = 0; i < THREAD_COUNT; i++)
  {
    SDL_WaitThread(pool->threads[i], NULL);
  }
}