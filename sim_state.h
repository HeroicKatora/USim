#ifndef _SIM_STATE_H_
#define _SIM_STATE_H_

#include <time.h>
#include <stdlib.h>

#include "particle.h"

typedef struct{
	int boxSize; //in k light years
	double mass_multiplier;
	int count;
	Particle** particles;
} Sim_state;

Sim_state *getNextState(Sim_state *state, double timestep);
Sim_state *state_initRandom(Sim_state* state);
Sim_state *state_setParticles(Sim_state* state, Particle** particles, int count);
Sim_state *state_createEmpty(int count, double mass_multiplier);
void state_calculate_effect(double grav_mul, Particle *a, Particle *b, Vector *speed_a, Vector *speed_b, short translation);
void state_free(Sim_state *sim);

#endif
