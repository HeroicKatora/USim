#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Vector;

Vector *vector_create(double x, double y);
void vector_free(Vector *v);

#endif
