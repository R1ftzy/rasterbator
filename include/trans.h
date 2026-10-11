#ifndef TRANS_H
#define TRANS_H
#include "types.h"

// Move a mesh (not setting coordinates)
void RB_translate_mesh3(mesh3 *mesh, float x_translate, float y_translate, float z_translate);

// Rotates a mesh about its centre (Euler)
void RB_rotate_mesh3_euler(mesh3 *mesh, float attitude, float heading, float bank);

// Rotates a mesh about its centre (Quaternion)
void RB_rotate_mesh3_quat(mesh3 *mesh, float w, float x, float y, float z);

// Scales a mesh
void RB_scale_mesh3(mesh3 *mesh, float x_scale, float y_scale, float z_scale);

// Get the centroid of a mesh
vec3 RB_get_centroid(mesh3 *mesh);

#endif