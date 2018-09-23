#include "mpiFunctions.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <mpi.h>

//akoloy8iakh 1 pyrhnas syneli3h xwris test

int main(int argc, char **argv){
	
	MPI_Init(&argc, &argv);
	
	srand(time(NULL));
	int **I0, **I1, i,j, k=0, colN=10, rowN=10;
	float **h;
	char* filter = "121242121"; //filter for convolution as a string to make it into the array "h"
	
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

	
	//sequential convolution for the whole array-image
	for(i=0; i<rowN; i++){ 
		for(j=0; j<colN; j++){
			int p,q;
			int conv=0;
			for(p=-1; p<=1; p++){
				for(q=-1; q<=1; q++){
					if( (i-p) < 0 || (j-q) < 0 || (i-p) >= rowN || (j-q) >= rowN ){
						//we're accessing p+1, q+1 for the h filter because it has rows/lines 0,1,2 and not -1,0,1
						conv += (float)I1[i][j]*h[p+1][q+1]; //if the neighbor doesn't exist add the value of the pixel we're convoluting instead
					}
					else{
						conv += (float)I1[i-p][j-q]*h[p+1][q+1];
					}
						
				}
			}
			I0[i][j] = conv;
			
		}
	}
	for(i=0; i<rowN; i++){
		if(i<3)
			free(h[i]);
		free(I1[i]);
		free(I0[i]);
	}
	free(I1);
	free(h);
	free(I0);
	
	MPI_Finalize();
}
