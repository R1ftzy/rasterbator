#ifndef TRANS_H
#define TRANS_H
#include "types.h"

void RB_translate_mesh3(mesh3 *mesh, float x_translate, float y_translate, float z_translate);

void RB_rotate_mesh3_euler(mesh3 *mesh, float attitude, float heading, float bank);

void RB_rotate_mesh3_quat(mesh3 *mesh, float w, float x, float y, float z);

void RB_scale_mesh3(mesh3 *mesh, float x_scale, float y_scale, float z_scale);

vec3 RB_get_centroid(mesh3 *mesh);

#endif