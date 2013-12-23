#include <stdio.h>

#include "sim_state.h"

#include "dbg.h"

int main(int argc, char **argv)
{
  #ifdef __DEBUG__
  printf("##### DEBUG VERSION #####\n");
  #endif

  int c = 500000;
  Sim_state *state = state_create_empty(c, 1);
  check_mem(state);
  
  state = state_initRandom(state);
  check_mem(state);
  
  state_free(&state);

  return 0;  
error:
  return 1;
}
