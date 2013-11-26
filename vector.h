#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>

typedef struct {
    double x;
    double y;
    double z;
} Vector;

Vector *vector_create(double x, double y, double z);
void vector_free(Vector **v);

#endif
