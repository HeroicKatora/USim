#include <stdio.h>

#include "sim_state.h"

#include "dbg.h"

int main(int argc, char **argv)
{
  #ifdef __DEBUG__
  printf("##### DEBUG VERSION #####\n");
  #endif

  int c = 500000;
  Sim_state *state = state_create_empty(c, (double)1.0, 100);
  check_mem(state);
  
  state = state_init_random(state);
  check_mem(state);
  
  Sim_state *state_new = get_next_state(state, (double)1.0);
  state_free(&state);

  state_free(&state_new);

  return 0;  
error:
  return 1;
}
