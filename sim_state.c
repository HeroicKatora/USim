#include "sim_state.h"

#include "dbg.h"

Sim_state *createEmpty(int count){
	Sim_state *s = (Sim_state *)malloc(sizeof(Sim_state));

	s->particles = (Particle**)calloc(count, sizeof(Particle*));

	s->count = count;

	return s;
}

Sim_state *getNextState(int timestep){
  return NULL;
}

Sim_state *initRandom(Sim_state* state){

	srand(time(NULL));
	int i;
	for(i = 0;i<state->count;i++){
		double x,y,z,m;
		x = (double)(rand())/RAND_MAX;
		y = (double)(rand())/RAND_MAX;
		z = (double)(rand())/RAND_MAX;
		m = 0.99+((double)(rand())/RAND_MAX);
		particle_free(state->particles[i]);
		state->particles[i] = particle_create(x,y,z,m);
	}
	return state;
}

Sim_state *setParticles(Sim_state* state, Particle** particles, int count){
	int i;
	for(i = state->count-1;i>=0;i--){
		particle_free(state->particles[i]);
		free(state->particles[i]);
	}
	state->count = count;
	state->particles = particles;
	return state;
}
