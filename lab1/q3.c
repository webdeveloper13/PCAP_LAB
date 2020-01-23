#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int a,b,answer;
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	a = atoi(argv[1]);
	b = atoi(argv[2]);
    switch(rank){
		case 0:
		answer=a+b;
		printf("Sum of %d and %d is %d\n",a,b,answer);
		break;

		case 1:
		answer=a-b;
		printf("Difference of %d and %d is %d\n",a,b,answer);
		break;

		case 2:
		answer=a*b;
		printf("Product of %d and %d is %d\n",a,b,answer);
		break;

		case 3:
		answer=a/b;
		printf("Quotient of %d and %d is %d\n",a,b,answer);
		break;
}

    MPI_Finalize();
	
	return 0;
}