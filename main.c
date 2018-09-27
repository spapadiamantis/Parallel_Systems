#include "convolution.h"
#include <math.h>
#include <unistd.h>

int main(int argc, char **argv){
	
	int **I0, **I1, i,j, k=0, colN, rowN, cores=1;
	float **h;
	char* filter = "121242121", c; //filter for convolution as a string to make it into the array "h"
	srand(time(NULL));
	
	while((c = getopt(argc, argv,"p:c:r:")) != -1){
        	switch(c)
        	{
            		case 'p':  //number of cores utilized
						//get the cores for each dimension(same number for both horizontal and vertical)
						//cores is both the vertical dimension(number of rows) and horizontal one(number of columns)
						cores = sqrt(atoi(optarg)); 
						break;
            		case 'c': //number of columns of pixels
                		colN = atoi(optarg);
                		break;
            		case 'r':  //number of rows of pixels
                		rowN = atoi(optarg);
                		break;
        	}
	}
	
	//allocate the two arrays and the filter we're working with at any point in the iterative convolution
	I0 = (int**)malloc( rowN * sizeof(int*) );
	I1 = (int**)malloc( rowN * sizeof(int*) );
	h = (float**)malloc( 3 * sizeof(float*) );
	for(i=0; i<rowN; i++){
		if(i<3)
			h[i] = (float*)malloc(3 * sizeof(float));
		I0[i] = (int*)malloc(colN * sizeof(int));
		I1[i] = (int*)malloc(colN * sizeof(int));
	}
	//construct the normalized h filter
	for(i=0; i<3; i++) 
		for(j=0; j<3; j++)
			h[i][j] = filter[k++] / 16;
	
	
	//fill the array with random numbers
	for(i=0; i<rowN; i++)
		for(j=0; j<colN; j++)
			I1[i][j]=rand()%255;
	if(cores <= 1) 
		//sequential convolution
		serialConv(I1, I0, h, rowN, colN);
	else{
		//utilize 4 or more cores
		int dims[2], periodic[2] = {0,0}, rowP, colP, coreTotal = cores*cores;
		
		MPI_Init(&argc, &argv);
		MPI_Datatype ROW, COLUMN;
		MPI_Status status;	
		
		MPI_Comm_size(MPI_COMM_WORLD,&coreTotal); //total number of processes
		MPI_Comm cartComm; //we'll be using cartesian topology for the processes
		
		//define process topology
		dims[0] = cores;
		dims[1] = cores;
		rowP = rowN / cores; //this is the number of rows in a process block
		colP = colN / cores; //this is the number of columns in a process block
		
		MPI_Cart_create(MPI_COMM_WORLD, DIMS, dims, periodic, 1, &cartComm);
		
		MPI_Finalize();
	}
	
	//free memory
	for(i=0; i<rowN; i++){
		if(i<3)
			free(h[i]);
		free(I1[i]);
		free(I0[i]);
	}
	free(I1);
	free(h);
	free(I0);
	
}