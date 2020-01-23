#include "mpi.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
int main(int argc, char *argv[])
{
	int rank,size,x;
	//int arr[MAX];
	//char str[MAX];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0)
	{
		int i,buffer_size;
		MPI_Pack_size(size,MPI_INT,MPI_COMM_WORLD,&buffer_size);
		buffer_size+=size*MPI_BSEND_OVERHEAD;
		void *buffer = malloc(buffer_size);
		MPI_Buffer_attach(buffer,buffer_size);

		printf("Enter %d elements \n",size-1);
		int arr[size];
		for(i=0;i<size;i++)
		{
			scanf("%d",&arr[i]);
		}

		for(i=0;i<size;i++)
		{
			MPI_Bsend(&arr[i],1,MPI_INT,i,99,MPI_COMM_WORLD);
		}

		MPI_Buffer_detach(&buffer,&buffer_size);

	}

	else
	{
		int n1;
		MPI_Status status;
		MPI_Recv(&n1,1,MPI_INT,0,99,MPI_COMM_WORLD,&status);

		if(rank%2==0)
		{

			printf("Square of %d in process %d is %d\n",n1,rank,n1*n1);
             
		}

		else
		{
			printf("Cube of %d in process %d is %d\n",n1,rank,n1*n1*n1);

		}

	}

	MPI_Finalize();


}
