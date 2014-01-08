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
  
  p->speed_old = vector_create(0, 0, 0);
  check_mem(p->speed_old);

  p->mass = mass;
  return p;
  
error:
  particle_free(&p);
  return NULL;
}

Particle *particle_join(Particle *a, Particle *b, Particle *write){
	if(!write) write = particle_create(0,0,0,a->mass+b->mass);
	{
		Vector posA, posB;
		vector_mul(a->position, a->mass, &posA);
		vector_mul(b->position, b->mass, &posB);
		vector_add_true(&posA, &posB);
		*write->position = posA;
		vector_div_true(write->position, a->mass+ b->mass);
	}
	{
		Vector movA,movB;
		vector_mul(a->speed,a->mass,&movA);
		vector_mul(b->speed,b->mass,&movB);
		vector_add_true(&movA, &movB);
		*write->speed = movA;
		vector_div_true(write->speed, a->mass+ b->mass);
	}
	{
		Vector movA,movB;
		vector_mul(a->speed_old,a->mass,&movA);
		vector_mul(b->speed_old,b->mass,&movB);
		vector_add_true(&movA, &movB);
		*write->speed_old = movA;
		vector_div_true(write->speed_old, a->mass+ b->mass);
	}
	write->mass = a->mass+b->mass;
	return write;
}


void particle_free(Particle **p)
{
  if(*p){
    if((*p)->position) vector_free(&(*p)->position);
    if((*p)->speed) vector_free(&(*p)->speed);
    if((*p)->speed_old) vector_free(&(*p)->speed_old);
    
    free(*p);
  }
  *p = NULL;
}
