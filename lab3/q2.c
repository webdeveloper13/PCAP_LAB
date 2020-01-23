#include "mpi.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
int main(int argc, char *argv[])
{
	int rank,size,N,M,i;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	N = atoi(argv[1]);
	M = atoi(argv[2]);
	    
	    int arr[M*N];
	    float b[N];

	
	if(rank==0)
	{
		N=size;
		fprintf(stdout, "Enter %d values:\n",N*M);
		fflush(stdout);
		int j = N*M;
		for(i=0;i<j;i++)
			scanf("%d",&arr[i]);
	}

	int c[M];
    MPI_Scatter(arr,M,MPI_INT,c,M,MPI_INT,0,MPI_COMM_WORLD);
	//fprintf(stdout,"I have recieved %d in process %d\n",c,rank);
	//fflush(stdout);
	float sum=0;
	for(i=0;i<M;i++)
	{
		sum+=c[i];
	}
	sum/=M;
	MPI_Gather(&sum,1,MPI_FLOAT,b,1,MPI_FLOAT,0,MPI_COMM_WORLD);

	if (rank==0)
	{
		fprintf(stdout, "The result gathered in the root\n");
		fflush(stdout);
		for(i=0;i<N;i++)
			fprintf(stdout, "%f\t",b[i]);
		fflush(stdout);
		printf("\n");
		float sum1=0;
		for(i=0;i<N;i++)
		{
			sum1+=b[i];
		}

		sum1/=N;

		fprintf(stdout, "The average is %f\n",sum1);
		fflush(stdout);
		
	}

	MPI_Finalize();
	return 0;
}




