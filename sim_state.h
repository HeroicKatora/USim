#ifndef _SIM_STATE_H_
#define _SIM_STATE_H_

#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "particle.h"
#include "vector_math.h"

typedef struct{
	int box_size; //in k light years
	double mass_multiplier;
	int count;
	Particle** particles;
} Sim_state;

Sim_state *get_next_state(Sim_state *state, double timestep);
Sim_state *state_init_random(Sim_state* state);
Sim_state *state_set_particles(Sim_state* state, Particle** particles, int count);
Sim_state *state_create_empty(int count, double mass_multiplier, double box_size);
void state_calculate_effect(double grav_mul, Particle *a, Particle *b, Vector *speed_a, Vector *speed_b, short translation);
void state_free(Sim_state **sim);

#endif
