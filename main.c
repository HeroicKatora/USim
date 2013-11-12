#include <stdio.h>

#include "particle.h"

#include "dbg.h"

int main(int argc, char **argv)
{
  #ifdef __DEBUG__
  printf("##### DEBUG VERSION #####\n");
  #endif

  int c = 1000000;
  
  int i = 0;
  Particle *vector[c];
  for(i = 0; i < c; i++){
    vector[i] = particle_create(i, i, i*2);
  }
  
  getchar();
  
  for(i = 0; i < c; i++){
    particle_free(vector[i]);
  }

  return 0;  
}
