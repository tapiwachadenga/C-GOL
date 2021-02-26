#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gol.h"

Cell **grid = NULL;

int main ( int argc, char **argv )
{
  grid = initializeGrid ();

  playGOL ( grid );

  return EXIT_SUCCESS;
}
