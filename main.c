#include <stdio.h>

#include "sim_state.h"

#include "dbg.h"
#include "time.h"

int main(int argc, char **argv)
{
  #ifdef __DEBUG__
  printf("##### DEBUG VERSION #####\n");
  #endif
  int c = (8000);
  Sim_state *state = state_create_empty(c, (double)30000.0, 10000);
  check_mem(state);
  state = state_init_random(state);
  check_mem(state);
  state_write(state);
  time_t t;
  t = time (NULL);

  printf("Gestartet um: %s\n", asctime(localtime(&t)));
  int rec = 0;
  for(rec = 0;rec < 500;rec++){
	  Sim_state *state_new = get_next_state(state, (double)1.0);
	  state_write(state_new);
	  state_free(&state);
	  state = state_new;
	  t = time(NULL);
	  printf("State %i um: %s\n",rec+1, asctime(localtime(&t)));
  }

  return 0;  
error:
  return 1;
}
