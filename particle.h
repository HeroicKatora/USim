#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "vector.h"
#include "vector_math.h"

typedef struct {
    double mass;
    Vector *position;
    Vector *speed;
    Vector *speed_old;
} Particle;

Particle *particle_create(double x, double y, double z, double mass);
Particle *particle_join(Particle *a, Particle *b, Particle *write);
void particle_free(Particle **p);

#endif
