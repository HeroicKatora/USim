#include "vector_math.h"

#include "dbg.h"

Vector *vector_add(Vector *a, Vector *b)
{
  double x = a->x + b-> x;
  double y = a->y + b-> y;
  double z = a->z + b-> z;
  return vector_create(x, y, z);
}

Vector *vector_sub(Vector *a, Vector *b)
{
  double x = a->x - b-> x;
  double y = a->y - b-> y;
  double z = a->z - b-> z;
  return vector_create(x, y, z);
}

Vector *vector_div(Vector *a, double d)
{
  double x = a->x / d;
  double y = a->y / d;
  double z = a->z / d;
  return vector_create(x, y, z);
}

Vector *vector_mul(Vector *a, double d)
{
  double x = a->x * d;
  double y = a->y * d;
  double z = a->z * d;
  return vector_create(x, y, z);
}

double vector_length(Vector *a)
{
  double x = a->x;
  double y = a->y;
  double z = a->z;
  return sqrt(x*x + y*y + z*z);
}

Vector *vector_normalize(Vector *a)
{
  return vector_div(a, vector_length(a));
}

Vector *vector_cross(Vector *a, Vector *b)
{
  double x = (a->y * b->z) - (a->z * b->y);
  double y = (a->z * b->x) - (a->x * b->z);
  double z = (a->x * b->y) - (a->y * b->x);
  return vector_create(x, y, z);
}

double vector_dot(Vector *a, Vector *b)
{
  return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

void vector_to_unitecube(Vector *a)
{
  if      (a->x > 1) {a->x = (a->x -1);}
  else if (a->x < 1) {a->x = (a->x +1);} 
  if      (a->y > 1) {a->y = (a->y -1);}
  else if (a->y < 1) {a->y = (a->y +1);}
  if      (a->z > 1) {a->z = (a->z -1);}
  else if (a->z < 1) {a->z = (a->z +1);}
}

