#ifndef OBJ_H
#define OBJ_H
#include "types.h"
// Reads obj files into a mesh
void RB_parse_obj(const char *filename, mesh3 *mesh);
#endif