#include "vector_math.h"

#include "dbg.h"

Vector *vector_add(Vector *a, Vector *b, Vector *write)
{
	if(!write) write = vector_create(0,0,0);
	write->x = a->x + b-> x;
	write->y = a->y + b-> y;
	write->z = a->z + b-> z;
 	return write;
}

Vector *vector_sub(Vector *a, Vector *b, Vector *write)
{
	if(!write) write = vector_create(0,0,0);
	write->x = a->x - b-> x;
	write->y = a->y - b-> y;
	write->z = a->z - b-> z;
	return write;
}

Vector *vector_div(Vector *a, double d, Vector *write)
{
	if(!write) write = vector_create(0,0,0);
	write->x = a->x / d;
	write->y = a->y / d;
	write->z = a->z / d;
	return write;
}

Vector *vector_mul(Vector *a, double d, Vector *write)
{
	if(!write) write = vector_create(0,0,0);
	write->x = a->x * d;
	write->y = a->y * d;
	write->z = a->z * d;
	return write;
}

inline double vector_length(Vector *a)
{
  double x = a->x;
  double y = a->y;
  double z = a->z;
  return sqrt(x*x + y*y + z*z);
}

inline Vector *vector_normalize(Vector *a)
{
	return vector_div(a, vector_length(a), NULL);
}

Vector *vector_cross(Vector *a, Vector *b, Vector *write)
{
	if(!write) write = vector_create(0,0,0);
	write->x = (a->y * b->z) - (a->z * b->y);
	write->y = (a->z * b->x) - (a->x * b->z);
	write->z = (a->x * b->y) - (a->y * b->x);
	return write;
}

inline double vector_dot(Vector *a, Vector *b)
{
  return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

void vector_to_unitcube(Vector *a)
{
  a->x -= (int)(a->x);
  if (a->x < 0) {a->x = (a->x +1);}
  a->y -= (int)(a->y);
  if (a->y < 0) {a->y = (a->y +1);}
  a->z -= (int)(a->z);
  if (a->z < 0) {a->z = (a->z +1);}
}

inline Vector *vector_add_true(Vector *a, Vector *b){
	return vector_add(a,b,a);
}

inline Vector *vector_sub_true(Vector *a, Vector *b){
	return vector_sub(a,b,a);
}

inline Vector *vector_div_true(Vector *a, double d)
{
	return vector_div(a,d,a);
}

inline Vector *vector_mul_true(Vector *a, double d)
{
	return vector_mul(a,d,a);
}

inline Vector *vector_normalize_true(Vector *a)
{
  return vector_div_true(a, vector_length(a));
}

