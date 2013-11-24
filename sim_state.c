#include "sim_state.h"

#include "dbg.h"

Sim_state *createEmpty(int count)
{
	Sim_state *s = (Sim_state *)malloc(sizeof(Sim_state));
	check_mem(s);

	s->particles = (Particle**)calloc(count, sizeof(Particle*));
	check_mem(s->particles);

	s->count = count;

	return s;
error:
	state_free(s);
	return NULL;
}

Sim_state *getNextState(Sim_state *state,int timestep)
{
	Sim_state *newState = createEmpty(state->count);
	//TODO Move particle
	double grav_multiplier = GRAVITATION_CONSTANT/(state->boxSize*state->boxSize);
	int i;
	for(i = 0;i<state->count;i++)
	{
		int j;
		for(j = i+1;j<state->count;j++)
		{

		}
	}
	//TODO Join near particles
	newState->boxSize = state->boxSize*exp(HUBBLE_PER_YEAR*timestep);
	return newState;
}

Sim_state *initRandom(Sim_state* state)
{

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

void state_particles_free(Sim_state *sim)
{
	if(sim&&sim->particles){
		int i;
		for(i = sim->count-1;i>=0;i--){
			particle_free(sim->particles[i]);
		}
		free(sim->particles);
	}
	sim->particles = NULL;
}

Sim_state *setParticles(Sim_state* state, Particle** particles, int count)
{
	state_particles_free(state);
	state->count = count;
	state->particles = particles;
	return state;
}

void state_free(Sim_state *sim)
{
	if(sim){
		state_particles_free(sim);
		free(sim);
	}
	sim = NULL;
}

