#include <mpi.h>
#include <stdio.h>

int factorial(int n) 
{
	if(n==0)
		return 1;
	else
		return n*factorial(n-1);
}

int sumofnatnos(int n)
{
	return n*(n+1)/2;
}

int main(int argc, char *argv[])
{
	int rank, size;
	int x, num;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;

	if(rank == 0) {
		int sum = 1;
		for(int i=1; i<size; i++)  {
			MPI_Recv(&x, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
			sum += x;
		}

		printf("Final Result : %d\n", sum);

	}

	else if(rank%2==0) {
		num = factorial(rank+1);
		MPI_Send(&num, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}

	else {
		num = sumofnatnos(rank+1);
		MPI_Send(&num, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;

}