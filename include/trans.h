#ifndef TRANS_H
#define TRANS_H
#include "types.h"

void moveMesh(mesh3 *mesh, float x_translate, float y_translate, float z_translate);

void rotateMesh(mesh3 *mesh, float attitude, float heading, float bank);

void scaleMesh(mesh3 *mesh, float x_scale, float y_scale, float z_scale);

#endif