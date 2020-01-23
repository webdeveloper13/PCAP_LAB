#include "mpi.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#define MAX 100
int main(int argc, char *argv[])
{
	int rank,size,x;
	//char str[MAX];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0)
	{
        printf("Please enter the value of x in master process\n");
		scanf("%d",&x);
		for(int i=1;i<size;i++)
		{
		MPI_Ssend(&x,1,MPI_INT,i,1,MPI_COMM_WORLD);
	   }
		fprintf(stdout, "I have sent %d from process 0\n",x);
		fflush(stdout);	

	}

	else
	{
		MPI_Status status;
		MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		fprintf(stdout, "I have recieved %d in process %d\n",x,rank);
		fflush(stdout);
	}

	MPI_Finalize();


}



