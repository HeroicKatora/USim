#include "particle.h"

#include "dbg.h"

Particle *particle_create(double x, double y, double z, double mass)
{
  Particle *p = (Particle *) malloc(sizeof(Particle));
  check_mem(p);
  
  p->position = vector_create(x, y, z);
  check_mem(p->position);
  
  p->speed = vector_create(0, 0, 0);
  check_mem(p->speed);
  
  p->mass = mass;
  return p;
  
error:
  particle_free(p);
  return NULL;
}

Particle *particle_join(Particle *a, Particle *b){
	//TODO implement
	return particle_create(0,0,0,0);
}

void particle_free(Particle *p)
{
  if(p){
    if(p->position) vector_free(p->position);
    if(p->speed) vector_free(p->speed);
    
    free(p);
  }
  p = NULL;
}
