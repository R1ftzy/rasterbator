#ifndef CAMERA_H
#define CAMERA_H
#include "types.h"
void init_cam(camera *cam);
mat4 cam_proj(camera *cam);
#endif