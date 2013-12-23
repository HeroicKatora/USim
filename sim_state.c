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
	state_free(&s);
	return NULL;
}

/*Calculate the effect of the particles on each other and store the resulting speed vectors in the given location.
Also treat them as if they were translated by one cube, described by the short.
Every two bit of translation refer to one axis(x are bits 3 and 4, y are 5&6,..).
The first bit toggles translation on and off, the seconds one describes which translation is used.
1 means b is translated by one cube in positive direction, 0 the other way.*/
void state_calculate_effect(double grav_mul, Particle *a, Particle *b, Vector *speed_a, Vector *speed_b, short translation){
	Vector pos_dif = *b->position;
	vector_sub_true(&pos_dif,a->position);
	if((translation&0b10)==0b10){
		int add = 1;
		if((translation&0b1)==0)add*=-1;
		pos_dif.z += add;
	}
	if((translation&0b1000)==0b1000){
		int add = 1;
		if((translation&0b100)==0)add*=-1;
		pos_dif.y += add;
	}
	if((translation&0b100000)==0b100000){
		int add = 1;
		if((translation&0b10000)==0)add*=-1;
		pos_dif.x += add;
	}
	grav_mul /= vector_length(&pos_dif)*vector_length(&pos_dif);
	vector_normalize_true(&pos_dif);

	{
		Vector i_mov_dif = pos_dif;
		vector_mul_true(&i_mov_dif,grav_mul*b->mass);
		vector_add_true(speed_a, &i_mov_dif);
	}

	{
		Vector j_mov_dif = pos_dif;
		vector_mul_true(&j_mov_dif,-grav_mul*a->mass);
		vector_add_true(speed_b, &j_mov_dif);
	}
}

//timestep in Ma
Sim_state *get_next_state(Sim_state *state,double timestep)
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
			//TODO multi-thread or multi compute, so move whole block to new function?
			int x;
			for(x = 0;x<32;x++){
				if((x&0b11)==0b01)x++;
				if((x&0b1100)==0b0100)x+=0b100;
				if((x&0b110000)==0b010000)x+=0b10000;
				state_calculate_effect(grav_multiplier, state->particles[i], state->particles[j], newState->particles[i]->speed, newState->particles[j]->speed, x);
			}
		}
	}
	//move particles
	for(i = 0;i<newState->count;i++){
		Vector movement = *newState->particles[i]->speed;
		vector_add_true(&movement, newState->particles[i]->speed_old);
		vector_mul_true(&movement, timestep/2);
		vector_add_true(newState->particles[i]->position, &movement);
		vector_to_unitcube(newState->particles[i]->position);
		*newState->particles[i]->speed_old = *newState->particles[i]->speed;
	}
	//join near and slow particles
	for(i = 0;i<newState->count;i++){
		int j;
		for(j = i+1;j<state->count;j++){
			Particle *pi = newState->particles[i];
			Particle *pj = newState->particles[j];
			//Check if they come into critical distance during next step
			Vector pos_dif = *(pj->position);
			vector_sub(&pos_dif, pi->position,&pos_dif);
			Vector mov_dif = *(pj->speed);
			vector_sub(&mov_dif, pi->speed,&mov_dif);
			int join = 0;
			//TODO review
			double a = mov_dif.x*mov_dif.x+mov_dif.y*mov_dif.y+mov_dif.z*mov_dif.z;
			double b = -2*(pos_dif.x*mov_dif.x+pos_dif.y*mov_dif.y+pos_dif.z*mov_dif.z);
			double c = pos_dif.x*pos_dif.x+pos_dif.y*pos_dif.y+pos_dif.z*pos_dif.z-CRITICAL_DISTANCE*CRITICAL_DISTANCE/(newState->boxSize*newState->boxSize);
			if(b*b >= 4*a*c){
				int time1 = (b-sqrt(b*b-4*a*c))/2*a;
				int time2 = (b+sqrt(b*b-4*a*c))/2*a;
				if(((time1 >= 0) && time1<timestep)||((time2 >= 0)&&time2<timestep)){
					join = 1;
				}
			}
			if(join){
				particle_join(pi, pj, pi);
				*pj = *(newState->particles[newState->count-1]);
				particle_free(&(newState->particles[newState->count-1]));
				newState->count--;
				//TODO REVIEW
				newState->particles = realloc(newState->particles, newState->count*sizeof(Particle*));
				j--;
			}
		}
	}

	newState->boxSize = state->boxSize*exp(HUBBLE_PER_YEAR*timestep);
	return newState;
}

Sim_state *state_init_random(Sim_state* state)
{

	srand(time(NULL));
	int i;
	for(i = 0;i<state->count;i++){
		double x,y,z,m;
		x = (double)(rand())/RAND_MAX;
		y = (double)(rand())/RAND_MAX;
		z = (double)(rand())/RAND_MAX;
		m = 0.99+((double)(rand())/RAND_MAX);
		particle_free(&(state->particles[i]));
		state->particles[i] = particle_create(x,y,z,m);
	}
	return state;
}

void state_particles_free(Sim_state *sim)
{
	if(sim&&sim->particles){
		int i;
		for(i = sim->count-1;i>=0;i--){
			particle_free(&(sim->particles[i]));
		}
		free(sim->particles);
	}
	sim->particles = NULL;
}

Sim_state *state_set_particles(Sim_state* state, Particle **particles, int count)
{
	state_particles_free(state);
	state->count = count;
	state->particles = particles;
	return state;
}

void state_free(Sim_state **sim)
{
	if(*sim){
		state_particles_free(*sim);
		free(*sim);
	}
	sim = NULL;
}

