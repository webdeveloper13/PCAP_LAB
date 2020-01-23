#include "mpi.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
int main(int argc, char *argv[])
{
	int rank,size;
	//int arr[MAX];
	//char str[MAX];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0){
		int x;
		MPI_Status status;
		printf("Enter the value of x\n");
		scanf("%d",&x);
		x=x+1;
		MPI_Send(&x,1,MPI_INT,1,1,MPI_COMM_WORLD);
		MPI_Recv(&x,1,MPI_INT,size-1,1,MPI_COMM_WORLD,&status);
		printf("Number finally is %d\n",x);
	}

	else if(rank==size-1){
		int x;
		MPI_Status status;
		MPI_Recv(&x,1,MPI_INT,size-2,1,MPI_COMM_WORLD,&status);
		x=x+1;
		MPI_Send(&x,1,MPI_INT,0,1,MPI_COMM_WORLD);

	}

	else
	{
		int x;
		MPI_Status status;
		MPI_Recv(&x,1,MPI_INT,rank-1,1,MPI_COMM_WORLD,&status);
		x=x+1;
		MPI_Send(&x,1,MPI_INT,rank+1,1,MPI_COMM_WORLD);

	}



	MPI_Finalize();
}