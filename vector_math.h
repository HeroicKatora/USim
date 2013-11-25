#ifndef _VECTOR_MATH_H_
#define _VECTOR_MATH_H_

#include <math.h>

#include "vector.h"

Vector *vector_add(Vector *a, Vector *b);
Vector *vector_sub(Vector *a, Vector *b);
Vector *vector_div(Vector *a, double d);
Vector *vector_mul(Vector *a, double d);
double vector_length(Vector *a);
Vector *vector_normalize(Vector *a);
Vector *vector_cross(Vector *a, Vector *b);
double vector_dot(Vector *a, Vector *b);
void vector_to_unitcube(Vector *a);
void vector_add_true(Vector *a, Vector *b);
void vector_sub_true(Vector *a, Vector *b);

#endif
