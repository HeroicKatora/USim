#include <stdio.h>

#include "sim_state.h"

#include "dbg.h"

int main(int argc, char **argv)
{
  #ifdef __DEBUG__
  printf("##### DEBUG VERSION #####\n");
  #endif
  int c = (8000);
  printf("%i \n", sizeof(argv));
  Sim_state *state = state_create_empty(c, (double)1.0, 100);
  check_mem(state);
  
  state = state_init_random(state);
  check_mem(state);
  state_write(state);
  int rec = 0;
  for(rec = 0;rec < 500;rec++){
	  Sim_state *state_new = get_next_state(state, (double)1.0);
	  state_write(state_new);
	  state_free(&state);
	  state = state_new;
  }

  return 0;  
error:
  return 1;
}
