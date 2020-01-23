#include "mpi.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100

int fact(int n) 
{
	if(n==0)
		return 1;
	else
		return n*fact(n-1);
}


int main(int argc, char *argv[])
{
	int rank,size,N,A[10],B[10],c,i;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);


	if(rank==0)
	{
		N=size;
		fprintf(stdout, "Enter %d values:\n",N);
		fflush(stdout);
		for(i=0;i<N;i++)
			scanf("%d",&A[i]);
	}

	MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
	fprintf(stdout,"I have recieved %d in process %d\n",c,rank);
	fflush(stdout);
	//c=c*c;
	c=fact(c);
	MPI_Gather(&c,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);

	if(rank==0)
	{
		fprintf(stdout, "The result gathered in the root\n");
		fflush(stdout);
		for(i=0;i<N;i++)
		fprintf(stdout, "%d\t",B[i]);
	    printf("\n");
		fflush(stdout);

		int sum=0;
		for(i=0;i<N;i++){

			sum=sum+B[i];
        }

		fprintf(stdout, "%d\t",sum);
		fflush(stdout);

	}

	MPI_Finalize();
	return 0;
}

