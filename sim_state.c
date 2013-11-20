/*
 * sim_state.c
 *
 *  Created on: 20.11.2013
 *      Author: Andreas_2
 */

#include "sim_state.h"

#include "particle.h"

#include "dbg.h"

#include <time.h>
#include <stdlib.h>

Sim_state *createEmpty(int count){
	Sim_state *s = (Sim_state *)malloc(sizeof(Sim_state));

	s->particles = (Particle**)calloc(count, sizeof(Particle*));

	s->count = count;

	return s;
}

Sim_state *getNextState(int timestep){

}
Sim_state *initRandom(Sim_state* state){

	srand(time(NULL));
	for(int i = 0;i<state->count;i++){
		double x,y,z,m;
		x = (double)(rand())/RAND_MAX;
		y = (double)(rand())/RAND_MAX;
		z = (double)(rand())/RAND_MAX;
		m = 0.99+((double)(rand())/RAND_MAX);
		free_particle(*(state->particles[i]));
		*(state->particles[i]) = create_particle(x,y,z,m);
	}
	return state;
}

Sim_state *setParticles(Sim_state* state, Particle** particles, int count){
	for(int i = state->count-1;i>=0;i--){
		free_particle(*(state->particles[i]));
		free(state->particles[i]);
	}
	state->count = count;
	state->particles = particles;
	return state;
}
