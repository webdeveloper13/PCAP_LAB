#include "mpi.h"
#include <stdio.h>
#define comm MPI_COMM_WORLD

int main(int argc, char const *argv[])
{
	int rank,size,N,A[100],B[100],c[100],i,m,sum=0,avg;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(comm,&rank);
	MPI_Comm_size(comm,&size);

	if(rank==0)
	{
		N=size;
		int arrsize;
		fprintf(stdout, "enter array size\n");
		scanf("%d",&arrsize);
		fprintf(stdout, "enter the array values:\n");
		fflush(stdout);
		for(i=0;i<arrsize;i++)
			scanf("%d",&A[i]);
		m=arrsize/N;
	}
	MPI_Bcast(&m,1,MPI_INT,0,comm);
	MPI_Scatter(A,m,MPI_INT,c,m,MPI_INT,0,comm);

	for(i=1;i<m;i++)
	{
		c[i]+=c[i-1];
	}

	MPI_Gather(c,m,MPI_INT,B,m,MPI_INT,0,comm);

	if(rank==0)
	{
		// int s=0;
		fprintf(stdout, "the result is gathered in the root\n");
		fflush(stdout);
		for(i=0;i<m*N;i++)
		{
			fprintf(stdout, "%d\t",B[i] );
			// s+=B[i];
		}
		// fprintf(stdout, "\nthe overall avg is : %d\n",s/m );
		// fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}