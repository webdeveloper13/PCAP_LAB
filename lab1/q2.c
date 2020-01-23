#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	/* code */
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank%2==0){
		printf("Hello from process %d\n",rank);
	}
	else{
		printf("World from process %d\n",rank);
	}
	MPI_Finalize();
	return 0;
}
