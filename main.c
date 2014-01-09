#include <stdio.h>

#include "sim_state.h"

#include "dbg.h"
#include "time.h"

int main(int argc, char **argv)
{
  #ifdef __DEBUG__
  printf("##### DEBUG VERSION #####\n");
  #endif
  int c = (512);
  Sim_state *state = state_create_empty(c, (double)1.0, 1000);
  check_mem(state);
  state = state_init_random(state);
  check_mem(state);
  state_write(state);
  time_t t;
  t = time (NULL);
  int rec = 0;
  for(rec = 0;rec < 500;rec++){
	  Sim_state *state_new = get_next_state(state, (double)1.0);
	  state_write(state_new);
	  state_free(&state);
	  state = state_new;
	  printf("Getting state %i in %f seconds\n",rec+1, difftime(time(NULL),t));
	  t = time(NULL);
  }

  return 0;  
error:
  return 1;
}
