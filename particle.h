#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "vector.h"

typedef struct {
    int mass;
    Vector *position;
    Vector *speed;
} Particle;

Particle *particle_create(double x, double y, double mass);
void particle_free(Particle *p);

#endif
