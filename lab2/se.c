#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int rank,size,x;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0)
	{
		printf("Please enter the value of n in master process\n");
		scanf("%d",&x);
		MPI_Send(&x,1,MPI_INT,1,1,MPI_COMM_WORLD);
		fprintf(stdout, "I have sent %d from process 0\n",x);
		fflush(stdout);
	}

	else
	{
		MPI_Status status;
		MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		fprintf(stdout, "I have recieved %d in process 1\n",x);
		fflush(stdout);
	}
	
	return 0;
}