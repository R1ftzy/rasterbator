#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "framebuffer.h"
#include "draw.h"
#include "color.h"
#include "vecmath.h"
#include "camera.h"
#include "config.h"
#include "obj.h"
#include "trans.h"
#include "RB_windows.h"
#include "thread_pool.h"

framebuffer fb;

typedef struct
{
  vec3 light;
  mesh3 base;
  mesh3 suzanne;
  mesh3 sphere;
  camera cam;
  float speed;
  float dt;
} scene;

void init(scene *m)
{
  init_cam(&m->cam);
  m->cam.eye = (vec3){4.0f, 0, 7};
  m->cam.target = (vec3){0, -1.0, 0};
  m->light = (vec3){2.0f, 0.5f, 8.0f};
  RB_fill(&fb, rgb(183, 183, 183));
  tri3 tris[] = {
      {{{-5.0f, -1.2f, 5.0f}, {5.0f, -1.2f, 5.0f}, {-5.0f, -1.2f, -5.0f}}},
      {{{-5.0f, -1.2f, -5.0f}, {5.0f, -1.2f, 5.0f}, {5.0f, -1.2f, -5.0f}}}};
  m->base.tris = malloc(sizeof(tris));
  memcpy(m->base.tris, tris, sizeof(tris));
  m->base.count = sizeof(tris) / sizeof(tris[0]);
  m->base.color = rgb(38, 48, 43);
  parse_obj("assets/Koenigsegg.obj", &m->suzanne);
  parse_obj("assets/icosphere.obj", &m->sphere);
  m->sphere.color = rgb(233, 234, 172);
  m->suzanne.color = rgb(239, 250, 251);
  translate_mesh3(&m->suzanne, 1.0, -0.9f, 1.0);
  rotate_mesh3_euler(&m->suzanne, 90, 0, 0);
  scale_mesh3(&m->sphere, 0.2, 0.2, 0.2);
  scale_mesh3(&m->suzanne, 0.7, 0.7, 0.7);
  translate_mesh3(&m->sphere, m->light.x, m->light.y, m->light.z);
  m->dt = 0;
  m->speed = 0.0;
}

void update(scene *m)
{
  m->speed += 1.2 * m->dt;
  float r = 4.0f;
  // m->cam.eye = (vec3){-8 * cosf(m->speed), sinf(m->speed * 2) + 3.0f, 8 * sinf(m->speed)};

  // vec3 prev_light = m->light;
  m->light = (vec3){r * cosf(2 * m->speed), 0.2, r * sinf(2 * m->speed)};
  // translate_mesh3(&m->sphere, m->light.x - prev_light.x, m->light.y - prev_light.y, m->light.z - prev_light.z);
  rotate_mesh3_euler(&m->sphere, 0.0f, 15 * m->dt, 0.0f);
  clear_framebuffer(&fb, rgb(183, 183, 183));
  // rotate_mesh3_euler(&m->suzanne, 0, 60 * m->dt, 0);
  float prev_sin = sinf(m->speed - 2 * m->dt);
  float curr_sin = sinf(m->speed);
  // translate_mesh3(&m->suzanne, 0, 0, 0.5 * (curr_sin - prev_sin));

  // RB_draw_mesh3d(&fb, &m->cam, m->base, m->light, rgb(38, 48, 43));
  // RB_draw_mesh3d(&fb, &m->cam, m->suzanne, m->light, rgb(239, 250, 251));
  // RB_draw_mesh3d(&fb, &m->cam, m->sphere, m->light, rgb(233, 234, 172));

  mesh3 *meshes[] = {
      &m->base,
      &m->suzanne,
      &m->sphere};

  int mesh_count = sizeof(meshes) / sizeof(meshes[0]);

  render_pool pool;
  rb_pool_render(&pool, &fb, &m->cam, meshes, mesh_count, m->light);
}

int main()
{
  scene m;
  RB_create_window();
  int frame_count = 0;
  float min_fps = 10000.0f;
  init(&m);
  // Game loop
  while (is_running())
  {
    update(&m);

    // framebuffer to window
    draw_frame();

    // Evaluate Delta Time
    {
      // Time in milliseconds
      m.dt = (float)get_delta_time() / 1000.0f;
      // Time in seconds
      m.dt /= 1000.0f;
    }

    if (min_fps > 1.0 / m.dt)
    {
      min_fps = 1.0f / m.dt;
    }
    // Checking Framerate
    if (frame_count % 30 == 0)
    {
      char title[64];
      snprintf(title, 64, "rasterbator | %.0f fps | %.0f fps min", 1.0f / m.dt, min_fps);
      RB_set_title(title);
    }
    if (frame_count % 1000 == 0)
    {
      min_fps = 10000.f;
    }
    frame_count++;
  }
  return 0;
}