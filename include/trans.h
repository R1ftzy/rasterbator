#ifndef TRANS_H
#define TRANS_H
#include "types.h"

void translate_mesh3(mesh3 *mesh, float x_translate, float y_translate, float z_translate);

void rotate_mesh3_euler(mesh3 *mesh, float attitude, float heading, float bank);

void rotate_mesh3_quat(mesh3 *mesh, float w, float x, float y, float z);

void scale_mesh3(mesh3 *mesh, float x_scale, float y_scale, float z_scale);

vec3 get_centroid(mesh3 *mesh);

#endif