#ifndef DRAW_H
#define DRAW_H
#include "framebuffer.h"

// Fills the entire framebuffer with a single color
void RB_fill(framebuffer *fb, uint32_t color);

// Draws a 2D line on the screen from point A to B
void RB_line2d(framebuffer *fb, vec2i A, vec2i B, uint32_t color);

// Draws a 3D line on the screen from point A to B
void RB_drawLine3d(framebuffer *fb, vec2i A, vec2i B, uint32_t color, float d0, float d1);

// Draws a 2D wireframe triangle
void RB_tri2d(framebuffer *fb, tri2 tri, uint32_t color);

// Draws a 2D filled triangle on the screen
void RB_fill_tri2d(framebuffer *fb, tri2 tri, uint32_t color);

// Draws a 3D wireframe triangle
void RB_tri3d(framebuffer *fb, camera *cam, tri3 tri, uint32_t color);

// Draws a 3D filled triangle
void RB_fill_tri3d(framebuffer *fb, camera *cam, tri3 tri, uint32_t color, int tile_y_min, int tile_y_max, mat4 view);

// void RB_draw_mesh3d(framebuffer *fb, camera *cam, mesh3 mesh, vec3 light, uint32_t color);

// Draws a scene with meshes with a single point light source
int RB_render_worker(void *arg);

typedef struct {
    framebuffer *fb;
    camera *cam;
    mesh3 **meshes;
    int mesh_count;
    // Temporary info
    vec3 light;
    
    int y_min;
    int y_max;
} mt_mesh_args;

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define LERP(a, b, t) ((a) * (1.0f - (t)) + (b) * (t))

#endif