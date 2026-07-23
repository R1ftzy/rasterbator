#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include <string.h>

#include <windows.h>

void parse_obj(const char *filename, mesh3 *mesh)
{
  char path[MAX_PATH];
  GetModuleFileNameA(NULL, path, MAX_PATH);
  *strrchr(path, '\\') = '\0'; 
  snprintf(path, MAX_PATH, "%s\\..\\%s", path, filename);
  puts(path);
  FILE *fp = fopen(path, "r");
  size_t v_capacity = 0;
  size_t t_capacity = 0;
  vec3 *vertices = NULL;
  size_t v_count = 0;
  tri3 *tris = NULL;
  size_t t_count = 0;
  char line[256];
  while (fgets(line, sizeof(line), fp))
  {
    if (line[0] == 'v' && line[1] == ' ')
    {
      if (v_count == v_capacity)
      {
        v_capacity = v_capacity ? v_capacity * 2 : 128;
        vertices = realloc(vertices, v_capacity * sizeof(vec3));
      }
      sscanf(line, "v %f %f %f", &vertices[v_count].x, &vertices[v_count].y, &vertices[v_count].z);
      v_count++;
    }

    if (line[0] == 'f' && line[1] == ' ')
    {
      if (t_count == t_capacity)
      {
        t_capacity = t_capacity ? t_capacity * 2 : 128;
        tris = realloc(tris, t_capacity * sizeof(tri3));
      }
      int a, b, c;
      sscanf(line, "f %d %d %d", &a, &b, &c);
      tris[t_count].v[0] = vertices[a - 1];
      tris[t_count].v[1] = vertices[b - 1];
      tris[t_count].v[2] = vertices[c - 1];

      t_count++;
    }
  }
  mesh->count = t_count;
  mesh->tris = malloc(mesh->count * sizeof(tri3));
  memcpy(mesh->tris, tris, mesh->count * sizeof(tri3));
}