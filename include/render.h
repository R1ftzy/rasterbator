#ifndef RENDER_H
#define RENDER_H
#include "types.h"

// Draws a scene with meshes with a single point light source
void RB_draw_meshes(mesh3 **meshes, int mesh_count, camera *cam, vec3 light);

#endif
