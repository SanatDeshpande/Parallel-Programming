// gameoflife.c
// Name: Sanat Deshpande
// JHED: sdeshpa4

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "mpi.h"

#define DEFAULT_ITERATIONS 64
#define GRID_WIDTH  256
#define DIM  16     // assume a square grid

int wrapX(int i, int x) {
    if (x < 0 && i % DIM == 0) { //left bound
        return DIM - 1; //pushes to right edge
    } else if (x > 0 && (i + 1) % DIM == 0) { //right bound
        return -1 * DIM + 1;
    } else {
        return x;
    }
}

int wrapY(int i , int y) {
    if (y < 0 && i >= 0 && i <= 15) { //top case
        return 240;
    } else if (y > 0 && i >= 240 && i <= 255) { //bottom case
        return -1 * 240;
    } else {
        return y;
    }
}

int main ( int argc, char** argv ) {

  int global_grid[ 256 ] =
   {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

  int* local_grid = malloc(sizeof(int) * GRID_WIDTH);
  memcpy(local_grid, global_grid, GRID_WIDTH * sizeof(int));

  int* test = malloc(sizeof(int) * 8);
  for (int t = 0; t < 8; t++) {
      test[t] = t;
  }

  // MPI Standard variable
  int num_procs;
  int ID, j;
  int iters = 0;
  int num_iterations;

  // Setup number of iterations
  if (argc == 1) {
    num_iterations = DEFAULT_ITERATIONS;
  }
  else if (argc == 2) {
    num_iterations = atoi(argv[1]);
  }
  else {
    printf("Usage: ./gameoflife <num_iterations>\n");
    exit(1);
  }

  // Messaging variables
  MPI_Status stat;
  // TODO add other variables as necessary

  // MPI Setup
  if ( MPI_Init( &argc, &argv ) != MPI_SUCCESS )
  {
    printf ( "MPI_Init error\n" );
  }

  int a = MPI_Comm_size ( MPI_COMM_WORLD, &num_procs ); // Set the num_procs
  int b = MPI_Comm_rank ( MPI_COMM_WORLD, &ID ); //which process
  assert ( DIM % num_procs == 0 );
  // TODO Setup your environment as necessary
  int data = 0;

  int next = (ID + 1) % num_procs;
  int prev;
  if (ID == 0) {
      prev = num_procs - 1;
  } else {
      prev = ID - 1;
  }
  int forwardRow = DIM * DIM * next / num_procs;
  int backwardRow;
  if (DIM * ID / num_procs > 0) {
      backwardRow = DIM * DIM * ID / num_procs - DIM;
  } else {
      backwardRow = 240; //hardcoded oh well
  }

  int forwardRowSent = (DIM * DIM * ID / num_procs ); //clean up redundancy if time
  int backwardRowSent;
  if (DIM * DIM * next / num_procs >= 256) {
      backwardRowSent = 240;
  } else {
      backwardRowSent = DIM * DIM * (ID+1) / num_procs - DIM;
  }

  int* tmpNextGen = malloc(sizeof(int) * GRID_WIDTH);
  for (int i = 0; i < GRID_WIDTH; i++) {
      tmpNextGen[i] = 0;
  }
  for ( iters = 0; iters < num_iterations; iters++ ) {

    // TODO: Add Code here or a function call to you MPI code
    //MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); sample call

    if (ID % 2 == 0) {
        //first group of message passing nodes
        if (num_procs > 1) {
            MPI_Send(&global_grid[backwardRowSent], DIM, MPI_INT, prev, 1, MPI_COMM_WORLD);
            MPI_Send(&global_grid[forwardRowSent], DIM, MPI_INT, next, 2, MPI_COMM_WORLD);
            //printf("%d %d\n", backwardRowSent, forwardRowSent);
            int* nextGen = malloc((forwardRowSent + DIM - backwardRowSent) * sizeof(int));
            int count = 0;
            for (int i = backwardRowSent; i < forwardRowSent + DIM - 1; i++) {
                int neighbors = 0;
                for (int vert = DIM *-1; vert < DIM*2; vert += DIM) {
                    for (int hor = -1; hor < 2; hor++) {
                        int x = wrapX(i, hor);
                        int y = wrapY(i, vert);
                        //printf("%d %d\n", x, y);
                        if (i + x + y == i) {
                            continue; //dont want to double count cell
                        }
                        if (local_grid[x + y + i] == 1) {
                            neighbors++;
                        }
                    }
                }
                if (global_grid[i] == 0 && neighbors == 3) {
                    nextGen[count] = 1;
                } else if (global_grid[i] == 1 && (neighbors == 2 || neighbors == 3)) {
                    nextGen[count] = 1;
                } else {
                    nextGen[count] = 0;
                }
                count++;
            }
            count = 0;
            for (int i = backwardRowSent; i < forwardRowSent + DIM - 1; i++) {
                global_grid[i] = nextGen[count];
                count++;
            }
            free(nextGen);

            MPI_Recv(&global_grid[forwardRow], DIM, MPI_INT, next, 2, MPI_COMM_WORLD, &stat);
            MPI_Recv(&global_grid[backwardRow], DIM, MPI_INT, prev, 1, MPI_COMM_WORLD, &stat);
        }
        if (ID == 0) {
            //sanity check code to compare correctness with serial implementation
            //safe since we dont use tmpNextGen outside
            for (int i = 0; i < GRID_WIDTH; i++) {
                int neighbors = 0;
                for (int vert = -1 * DIM; vert < DIM*2; vert+=DIM) {
                    for (int hor = -1 ; hor < 2; hor++) {
                        int x = wrapX(i, hor);
                        int y = wrapY(i, vert);
                        //printf("%d %d\n", x, y);
                        if (i + x + y == i) {
                            continue; //dont want to double count cell
                        }
                        if (local_grid[x + y + i] == 1) {
                            neighbors++;
                        }
                    }
                }
                if (local_grid[i] == 0 && neighbors == 3) {
                    tmpNextGen[i] = 1;
                } else if (local_grid[i] == 1 && (neighbors == 2 || neighbors == 3)) {
                    tmpNextGen[i] = 1;
                } else {
                    tmpNextGen[i] = 0;
                }
            }
            memcpy(local_grid, tmpNextGen, GRID_WIDTH * sizeof(int));
            memcpy(global_grid, tmpNextGen, GRID_WIDTH * sizeof(int));
            //above copied for later matching/checking
        }
        //end sanity check...
    } else {
        //second group of message passing nodes
        MPI_Recv(&global_grid[forwardRow], DIM, MPI_INT, next, 1, MPI_COMM_WORLD, &stat);
        MPI_Recv(&global_grid[backwardRow], DIM, MPI_INT, prev, 2, MPI_COMM_WORLD, &stat);
        //printf("%d %d\n", backwardRowSent, forwardRowSent);
        //printf("%d %d\n%d %d\n\n", backwardRow, forwardRow, backwardRowSent, forwardRowSent);
        int* nextGen = malloc((forwardRowSent + DIM - backwardRowSent) * sizeof(int));
        int count = 0;
        for (int i = backwardRowSent; i < forwardRowSent + DIM - 1; i++) {
            int neighbors = 0;
            for (int vert = DIM *-1; vert < DIM*2; vert += DIM) {
                for (int hor = -1; hor < 2; hor++) {
                    int x = wrapX(i, hor);
                    int y = wrapY(i, vert);
                    //printf("%d %d\n", x, y);
                    if (i + x + y == i) {
                        continue; //dont want to double count cell
                    }
                    if (local_grid[x + y + i] == 1) {
                        neighbors++;
                    }
                }
            }
            if (global_grid[i] == 0 && neighbors == 3) {
                nextGen[count] = 1;
            } else if (global_grid[i] == 1 && (neighbors == 2 || neighbors == 3)) {
                nextGen[count] = 1;
            } else {
                nextGen[count] = 0;
            }
            count++;
        }
        count = 0;
        for (int i = backwardRowSent; i < forwardRowSent + DIM - 1; i++) {
            global_grid[i] = nextGen[count];
            count++;
        }
        free(nextGen);
        MPI_Send(&global_grid[backwardRowSent], DIM, MPI_INT, prev, 2, MPI_COMM_WORLD);
        MPI_Send(&global_grid[forwardRowSent], DIM, MPI_INT, next, 1, MPI_COMM_WORLD);
    }


    //Sanity check error
    if (memcmp(global_grid, tmpNextGen, GRID_WIDTH * sizeof(int)) != 0) {
        //fprintf(stderr, "%s\n", "DOES NOT MATCH\n");
    }
    //-----------------
    // Output the updated grid state
    if ( ID == 0 ) {
      printf ( "\nIteration %d: final grid:\n", iters );

      for ( j = 0; j < GRID_WIDTH; j++ ) {
        if ( j % DIM == 0 ) {
          printf( "\n" );
        }
        printf ( "%d  ", global_grid[j] );
      }
      printf( "\n" );
    }
  }

  // TODO: Clean up memory
  MPI_Finalize(); // finalize so I can exit
  free(test);
}
