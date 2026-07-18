#include "types.h"
#include "vecmath.h"
#include <math.h>
#include <stdio.h>

void applyTransformation(mesh3 *mesh, mat4 mat)
{
  for (size_t i = 0; i < mesh->count; i++)
  {
    vec4 v0 = VEC3_TO_VEC4(mesh->tris[i].v[0]);
    vec4 v1 = VEC3_TO_VEC4(mesh->tris[i].v[1]);
    vec4 v2 = VEC3_TO_VEC4(mesh->tris[i].v[2]);

    vec4 o0 = mat4MulVec4(mat, v0);
    vec4 o1 = mat4MulVec4(mat, v1);
    vec4 o2 = mat4MulVec4(mat, v2);

    vec3 t0 = {o0.x, o0.y, o0.z};
    vec3 t1 = {o1.x, o1.y, o1.z};
    vec3 t2 = {o2.x, o2.y, o2.z};

    mesh->tris[i] = (tri3){t0, t1, t2};
  }
}

vec3 getCentroid(mesh3 *mesh)
{
  vec3 centroid = {0};
  for (size_t i = 0; i < mesh->count; i++)
  {
    centroid = vec3Add(centroid, vec3Add(vec3Add(mesh->tris[i].v[0], mesh->tris[i].v[1]), mesh->tris[i].v[2]));
  }
  centroid.x /= 3 * mesh->count;
  centroid.y /= 3 * mesh->count;
  centroid.z /= 3 * mesh->count;

  return centroid;
}

void moveMesh(mesh3 *mesh, float x_translate, float y_translate, float z_translate)
{
  mat4 matMove = {0};
  matMove.m[0][0] = 1;
  matMove.m[1][1] = 1;
  matMove.m[2][2] = 1;
  matMove.m[0][3] = x_translate;
  matMove.m[1][3] = y_translate;
  matMove.m[2][3] = z_translate;
  matMove.m[3][3] = 1;

  applyTransformation(mesh, matMove);
}

void rotateMeshQuat(mesh3 *mesh, float w, float x, float y, float z)
{
  vec3 centroid = getCentroid(mesh);
  moveMesh(mesh, -centroid.x, -centroid.y, -centroid.z);
  mat4 matRot = {0};
  matRot.m[0][0] = 1 - 2 * (y * y + z * z);
  matRot.m[0][1] = 2 * (x * y - w * z);
  matRot.m[0][2] = 2 * (x * z + w * y);

  matRot.m[1][1] = 1 - 2 * (x * x + z * z);
  matRot.m[1][2] = 2 * (y * z - w * x);
  matRot.m[1][0] = 2 * (x * y + w * z);

  matRot.m[2][2] = 1 - 2 * (x * x + y * y);
  matRot.m[2][0] = 2 * (x * z - w * y);
  matRot.m[2][1] = 2 * (y * z + w * x);

  applyTransformation(mesh, matRot);

  moveMesh(mesh, centroid.x, centroid.y, centroid.z);
}

void rotateMeshEuler(mesh3 *mesh, float attitude, float heading, float bank)
{
  float c1 = cosf(DEG_TO_RAD(heading) / 2);
  float c2 = cosf(DEG_TO_RAD(bank) / 2);
  float c3 = cosf(DEG_TO_RAD(attitude) / 2);
  float s1 = sinf(DEG_TO_RAD(heading) / 2);
  float s2 = sinf(DEG_TO_RAD(bank) / 2);
  float s3 = sinf(DEG_TO_RAD(attitude) / 2);
  quat q;
  q.w = c1 * c2 * c3 - s1 * s2 * s3;
  q.x = c1 * c2 * s3 + s1 * s2 * c3;
  q.y = s1 * c2 * c3 + c1 * s2 * s3;
  q.z = c1 * s2 * c3 - s1 * c2 * s3;
  rotateMeshQuat(mesh, q.w, q.x, q.y, q.z);
}

void scaleMesh(mesh3 *mesh, float x_scale, float y_scale, float z_scale)
{
  mat4 matScale = {0};
  matScale.m[0][0] = x_scale;
  matScale.m[1][1] = y_scale;
  matScale.m[2][2] = z_scale;
  matScale.m[3][3] = 1;
  applyTransformation(mesh, matScale);
}