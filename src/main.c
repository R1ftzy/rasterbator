#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
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

extern framebuffer fb;

typedef struct
{
  vec3 light;
  mesh3 base;
  mesh3 sonic;
  mesh3 sphere;
  camera cam;
  float speed;
  float dt;
} scene;

void init(scene *m)
{
  initCam(&m->cam);
  m->light = (vec3){-1.0f, -0.5f, 2.0f};
  fill(&fb, rgb(183, 183, 183));
  tri3 tris[] = {
      {{{-5.0f, -1.8f, 3.0f}, {-5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 3.0f}}},
      {{{-5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 3.0f}}}};
  m->base.tris = malloc(sizeof(tris));
  memcpy(m->base.tris, tris, sizeof(tris));
  m->base.count = sizeof(tris) / sizeof(tris[0]);
  parse_obj("assets/Sonic.obj", &m->sonic);
  parse_obj("assets/icosphere.obj", &m->sphere);
  moveMesh(&m->sonic, 0, 0, 3.5);
  rotateMeshEuler(&m->sonic, 90, -45, 0);
  scaleMesh(&m->sphere, 0.2, 0.2, 0.2);
  moveMesh(&m->sphere, m->light.x, m->light.y, m->light.z);
  m->dt = 0;
  m->speed = 0.0;
}

void update(scene *m)
{
  m->speed += 2 * m->dt;
  float r = 2.0f;
  vec3 prev_light = m->light;
  m->light = (vec3){r * cosf(m->speed), 0.0f, r * sinf(m->speed) + 3.5};
  moveMesh(&m->sphere, m->light.x - prev_light.x, m->light.y - prev_light.y, m->light.z - prev_light.z);
  rotateMeshEuler(&m->sphere, 0.0f, 15 * m->dt, 0.0f);
  clear_framebuffer(&fb, rgb(183, 183, 183));
  rotateMeshEuler(&m->sonic, 0, 60 * m->dt, 0);
  float prev_sin = sinf(m->speed - 2 * m->dt);
  float curr_sin = sinf(m->speed);
  // moveMesh(&m->sonic, 0, 0, 0.5 * (curr_sin - prev_sin));
  drawMesh3d(&fb, &m->cam, m->base, m->light, rgb(140, 183, 76));
  drawMesh3d(&fb, &m->cam, m->sonic, m->light, rgb(89, 135, 199));
  drawMesh3d(&fb, &m->cam, m->sphere, m->light, rgb(233, 234, 172));
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
      wchar_t title[64];
      swprintf(title, 64, L"rasterbator | %.0f fps | %.0f fps min", 1.0f / m.dt, min_fps);
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