#ifndef _VECTOR_MATH_H_
#define _VECTOR_MATH_H_

#include <math.h>

#include "vector.h"

Vector *vector_add(Vector *a, Vector *b, Vector *write);
Vector *vector_sub(Vector *a, Vector *b, Vector *write);
Vector *vector_div(Vector *a, double d, Vector *write);
Vector *vector_mul(Vector *a, double d, Vector *write);
inline double vector_length(Vector *a);
inline Vector *vector_normalize(Vector *a);
Vector *vector_cross(Vector *a, Vector *b, Vector *write);
inline double vector_dot(Vector *a, Vector *b);
void vector_to_unitcube(Vector *a);
inline Vector *vector_add_true(Vector *a, Vector *b);
inline Vector *vector_sub_true(Vector *a, Vector *b);
inline Vector *vector_div_true(Vector *a, double d);
inline Vector *vector_mul_true(Vector *a, double d);
inline Vector *vector_normalize_true(Vector *a);
Vector *vector_shorten_in_cube(Vector *a, Vector *write);

#endif
