/*
 * sim_state.h
 *
 *  Created on: 20.11.2013
 *      Author: Andreas_2
 */

#ifndef SIM_STATE_H_
#define SIM_STATE_H_

typedef struct{
	int boxSize; //in k light years
	int count;
	Particle** particles;
} Sim_state;

Sim_state *getNextState(int timestep);
Sim_state *initRandom(Sim_state* state);
Sim_state *setParticles(Sim_state* state, Particle** particles, int count);
Sim_state *createEmpty(int count);

#endif /* SIM_STATE_H_ */
