#include "vector.h"

#include "dbg.h"

Vector *vector_create(double x, double y, double z)
{
  Vector *v = (Vector *) malloc(sizeof(Vector));
  check_mem(v);
  v->x = x;
  v->y = y;
  v->z = z;
  return v;
  
error:
  vector_free(&v);
  return NULL;
}

void vector_free(Vector **v)
{
  if(*v) free(*v);
  *v = NULL;
}
