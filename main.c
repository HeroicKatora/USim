#include <stdio.h>

#include "sim_state.h"

#include "dbg.h"

int main(int argc, char **argv)
{
  #ifdef __DEBUG__
  printf("##### DEBUG VERSION #####\n");
  #endif
  int c = (512);
  printf("%i \n", sizeof(argv));
  Sim_state *state = state_create_empty(c, (double)1.0, 50);
  check_mem(state);
  
  state = state_init_random(state);
  check_mem(state);
  printf("Writing state:\n");
  state_write(state);
  printf("Computing state:\n");
  int rec = 0;
  for(rec = 0;rec < 50;rec++){
	  Sim_state *state_new = get_next_state(state, (double)1.0);
	  state_write(state_new);
	  state_free(&state);
	  state = state_new;
  }

  return 0;  
error:
  return 1;
}
