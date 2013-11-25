#include "sim_state.h"

#include "dbg.h"

Sim_state *state_create_empty(int count, double mass_multiplier)
{
	Sim_state *s = (Sim_state *)malloc(sizeof(Sim_state));
	check_mem(s);

	s->particles = (Particle**)calloc(count, sizeof(Particle*));
	check_mem(s->particles);

	s->count = count;
	s->mass_multiplier = mass_multiplier;

	return s;
error:
	state_free(s);
	return NULL;
}

/*Calculate the effect of the particles on each other and store the resulting speed vectors in the given location.
Also treat them as if they were translated by one cube, described by the short.
Every two bit of translation refer to one axis(x are bits 3 and 4, y are 5&6,..).
The first bit toggles translation on and off, the seconds one describes which translation is used.
1 means b is translated by one cube in positive direction, 0 the other way.*/
void state_calculate_effect(double grav_mul, Particle *a, Particle *b, Vector *speed_a, Vector *speed_b, short translation){
	Vector *pos_dif = vector_sub(b->position,a->position);
	if((translation&0b10)==0b10){
		int add = 1;
		if((translation&0b1)==0)add*=-1;
		pos_dif->z += add;
	}
	if((translation&0b1000)==0b1000){
		int add = 1;
		if((translation&0b100)==0)add*=-1;
		pos_dif->y += add;
	}
	if((translation&0b100000)==0b100000){
		int add = 1;
		if((translation&0b10000)==0)add*=-1;
		pos_dif->x += add;
	}
	grav_mul /= vector_length(pos_dif)*vector_length(pos_dif);
	Vector *dif_unit = vector_normalize(pos_dif);
	free(pos_dif);

	{
	Vector *i_mov_dif = vector_mul(dif_unit,grav_mul*b->mass);
	Vector *i_new_mov = vector_add(a->speed, i_mov_dif);
	free(i_mov_dif);
	*(speed_a) = *i_new_mov;
	free(i_new_mov);
	}

	{
	Vector *j_mov_dif = vector_mul(dif_unit,-grav_mul*a->mass);
	Vector *j_new_mov = vector_add(b->speed, j_mov_dif);
	free(j_mov_dif);
	*(speed_b) = *j_new_mov;
	free(j_new_mov);
	}
}

//timestep in Ma
Sim_state *getNextState(Sim_state *state,double timestep)
{
	//Create a copy of the state
	Sim_state *newState = state_create_empty(state->count, state->mass_multiplier);
	int i;
	for(i = 0;i<newState->count;i++){
		Vector *pos = state->particles[i]->position;
		newState->particles[i] = particle_create(pos->x,pos->y,pos->z,state->particles[i]->mass);
	}
	//Calculate new movement of particles
	double grav_multiplier = GRAVITATION_CONSTANT/(state->boxSize*state->boxSize);
	grav_multiplier *= state->mass_multiplier*timestep;

	for(i = 0;i<state->count;i++)
	{
		int j;
		for(j = i+1;j<state->count;j++)
		{
			int x;
			for(x = 0;x<32;i++){
				if((x&0b11)==0b01)x++;
				if((x&0b1100)==0b0100)x+=0b100;
				if((x&0b110000)==0b010000)x+=0b10000;
				state_calculate_effect(grav_multiplier, state->particles[i], state->particles[j], newState->particles[i]->speed, newState->particles[j]->speed, x);
			}
			//TODO move into box again if outside
		}
	}
	//move particles
	for(i = 0;i<newState->count;i++){
		Vector *movement = vector_mul(newState->particles[i]->speed, timestep);
		Vector *new_pos = vector_add(movement, newState->particles[i]->position);
		free(movement);
		*(newState->particles[i]->position) = *new_pos;
		free(new_pos);
	}
	//join near and slow particles
	for(i = 0;i<newState->count;i++){
		int j;
		for(j = i+1;j<state->count;j++){
			Particle *i = newState->particles[i];
			Particle *j = newState->particles[j];
			Vector *pos_dif = vector_sub(j->position, i->position);
			Vector *mov_dif = vector_sub(j->speed, i->speed);
			//TODO proper join check
			if(vector_length(pos_dif) < 0.0){
				Particle *joined = particles_join(i, j);
				*i = *joined;
				free(joined);
				*j = *(newState->particles[newState->count]);
				particle_free(newState->particles[newState->count]);
				newState->count--;
				//TODO we now have one unused pointer allocated in memory. Maybe do sth?
				j--;
			}
		}
	}

	newState->boxSize = state->boxSize*exp(HUBBLE_PER_YEAR*timestep);
	return newState;
}

Sim_state *state_initRandom(Sim_state* state)
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

Sim_state *state_setParticles(Sim_state* state, Particle** particles, int count)
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

