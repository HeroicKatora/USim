#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "vector.h"

typedef struct {
    double mass;
    Vector *position;
    Vector *speed;
} Particle;

Particle *particle_create(double x, double y, double z, double mass);
Particle *particle_join(Particle *a, Particle *b);
void particle_free(Particle **p);

#endif
