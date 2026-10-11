#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#ifdef _WIN32
#include <windows.h>

#elif defined(__linux__)
#include <unistd.h>

#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

enum
{
  EXE_PATH_MAX = 1024
};

void RB_parse_obj(const char *filename, mesh3 *mesh)
{
  char path[EXE_PATH_MAX];
  char full[EXE_PATH_MAX];
  const char *sep = NULL;

#ifdef _WIN32
  if (GetModuleFileNameA(NULL, path, (DWORD)sizeof(path)) == 0)
  {
    mesh->count = 0;
    mesh->tris = NULL;
    return;
  }
#elif defined(__linux__)
  ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
  if (len < 0)
  {
    mesh->count = 0;
    mesh->tris = NULL;
    return;
  }
  path[len] = '\0';
#elif defined(__APPLE__)
  uint32_t size = (uint32_t)sizeof(path);
  if (_NSGetExecutablePath(path, &size) != 0)
  {
    mesh->count = 0;
    mesh->tris = NULL;
    return;
  }
#endif
  path[sizeof(path) - 1] = '\0';

  sep = strrchr(path, '/');
  {
    char *bs = strrchr(path, '\\');
    if (bs > sep)
      sep = bs;
  }
  if (!sep)
  {
    mesh->count = 0;
    mesh->tris = NULL;
    return;
  }
  *((char *)sep) = '\0';

  snprintf(full, sizeof(full), "%s/../%s", path, filename);

  FILE *fp = fopen(full, "r");
  if (!fp)
  {
    mesh->count = 0;
    mesh->tris = NULL;
    return;
  }
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
  fclose(fp);

  mesh->count = t_count;
  mesh->tris = malloc(mesh->count * sizeof(tri3));
  memcpy(mesh->tris, tris, mesh->count * sizeof(tri3));

  free(vertices);
  free(tris);
}