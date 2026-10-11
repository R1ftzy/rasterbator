#include "render.h"
#include "framebuffer.h"
#include "thread_pool.h"

void RB_draw_meshes(mesh3 **meshes, int mesh_count, camera *cam, vec3 light)
{
  static render_pool pool;
  RB_pool_render(&pool, &fb, cam, meshes, mesh_count, light);
}
