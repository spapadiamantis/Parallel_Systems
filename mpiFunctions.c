#include "mpiFunctions.h"


//Input: the process with rank = my_rank
//Output:returns a array with her 8 neighbors of the process
int *findProcessNeighbors(MPI_Comm comm, int my_rank){
   /* int *nbrs = malloc(8*sizeof(int));
    int coords[2];
    int temp_rank;
    MPI_Cart_shift(comm,0, 1, &nbrs[UP], &nbrs[DOWN]);
    MPI_Cart_shift(comm,1,1, &nbrs[LEFT], &nbrs[RIGHT]);
    
    MPI_Cart_coords(comm,nbrs[UP],2,coords);
    coords[1]+=1;
    MPI_Cart_rank(comm,coords,&nbrs[UP_RIGHT]);
    coords[1]-=2;
    MPI_Cart_rank(comm,coords,&nbrs[UP_LEFT]);
    coords[0]+=2;
    MPI_Cart_rank(comm,coords,&nbrs[DOWN_LEFT]);
    coords[1]+=2;
    MPI_Cart_rank(comm,coords,&nbrs[DOWN_RIGHT]);
    return nbrs; */
}