#ifndef CAMERA_H
#define CAMERA_H
#include "types.h"

void RB_init_cam(camera *cam);

mat4 RB_cam_proj(camera *cam);

mat4 RB_look_at_matrix(camera *cam);

mat4 RB_update_view(camera *cam);

#endif