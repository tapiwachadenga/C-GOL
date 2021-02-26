#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include "gol.h"

const int x = 17;
const int y = 25;

void nextGen ( Cell **cell ) 
{
  for ( int i = 0; i < x; i++ ) 
  {
    for ( int j = 0; j < y; j++ )
    {

      int cond = ( *( cell + i ) + j )->condition;
      int state = ( *( cell + i ) + j )->state;

      if ( cond == 3 && state == 0 )
        ( *( cell + i ) + j )->state = 1;
      else if ( ( cond < 2 || cond > 3 ) && state == 1 )
      {
        ( *( cell + i ) + j )->state = 0;
      }
      else
      {
         ( *( cell + i ) + j )->state = state;
      }
    }
  }
}

int onesDistribution ( int bias ) 
{
  int n = rand () % 100 + 1;
  if ( n <= bias ) return 1;
  return 0;
}

Cell **initializeGrid ( ) 
{
   
  Cell **grid = ( Cell ** ) malloc ( sizeof ( Cell * ) * x );
  for ( int i = 0; i < x; i++ ) 
    grid [i] = ( Cell * ) malloc ( sizeof ( Cell ) * y ); 

  int z = 0;
  for ( int i = 0 ; i < x ; i ++ ) 
  {
    for ( int j = 0; j < y ; j++, z++ ) 
    {
       Cell *newCell = ( Cell * ) malloc ( sizeof ( Cell ) );
       newCell->state = onesDistribution ( 25 );
       *( *( grid + i ) + j )  = *newCell;
    }
  }
  return grid;
}

void printGrid ( Cell **grid )
{
  fprintf ( stdout, "\n" );
  for ( int i = 0; i < x ; i++ )
  {
    for ( int j = 0; j < y; j++ )
   {
      char color [] ="\033[1;33m";	   
      int st = ( *( grid + i ) + j )->state;
      if ( st == 1 ) strcpy ( color, "\033[1;31m" );

      fprintf ( stdout, "%s" , color );
      fprintf ( stdout, " %d ", st );
   }
     fprintf ( stdout, "\n\n" );
  }
}

void getConditions ( Cell **grid ) 
{
  for ( int i = 0; i < x; i ++ ) 
  {
    for ( int j = 0; j < y; j ++ ) 
    {
      
      ( *( grid + i ) + j )->condition = ( *( grid + ( i + x ) % x ) 
		                                   + ( j  - 1 + y ) % y )->state +
	        			 ( *( grid + ( i - 1 + x ) % x ) 
					           + ( j - 1 + y ) % y )->state +
                                         ( *( grid + ( i - 1 + x ) % x ) 
					           + ( j + y ) % y )->state +
                                         ( *( grid + ( i - 1 + x ) % x ) 
					           + ( j + 1 + y ) % y )->state +
                                         ( *( grid + ( i + x ) % x ) 
					           + ( j + 1 + y ) % y )->state +
                                         ( *( grid + ( i + 1 + x ) % x ) 
					           + ( j + 1 + y ) % y )->state +
                                         ( *( grid + ( i + 1 + x ) % x ) 
					           + ( j + y ) % y )->state + 
					 ( *( grid + ( i + 1 + x ) % x ) 
					           + ( j - 1 + y ) % y )->state;
    }
  }
}

void playGOL ( Cell **grid )
{
  int count = 0;
  while ( true )
  {
    system("cls");
    fprintf ( stdout, "\033[0m" );
    fprintf ( stdout, "\n     *************************      GEN %d     ***********************\n", count );
    printGrid ( grid );
    fprintf ( stdout, "\033[0m" );
    fprintf ( stdout, "\n\t **********************************************************\n");
  
    //fprintf ( stdout, "sleep" );
    getConditions ( grid );
    //fprintf ( stdout, "\tConditions" );
    nextGen ( grid );
    //fprintf ( stdout, "\tsleep" );
    count++;
    sleep ( 2 );
  }
}
