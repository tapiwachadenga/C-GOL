#ifndef GOL_H
#define GOL_H

typedef struct Cell
{
  int state;
  int condition;
}Cell;

Cell **initializeGrid ( );

void printGrid ( Cell **grid );

void getConditions ( Cell**grid );

int onesDistribution ( int n );

void nextGen ( Cell **cells );

void playGOL ( Cell **grid );

#endif 
