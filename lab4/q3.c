#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define comm MPI_COMM_WORLD

int keyCount(int k, int n, int arr[]){
	int count = 0;
	for(int i=0; i<n; i++)
		if(arr[i] == k)
			count++;
	return count;
}

int main(int argc, char const *argv[])
{
	int n, rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(comm, &n);
	MPI_Comm_rank(comm, &rank);
	int mat[n][n];
	int key;
	if(rank == 0){
		printf("Enter %d * %d matrix\n", n, n);
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				scanf("%d", &mat[i][j]);
		printf("Enter element to search for\n");
		scanf("%d", &key);
	}
	MPI_Bcast(&key, 1, MPI_INT, 0, comm);
    int row[n];
	MPI_Scatter(mat, n, MPI_INT, row, n, MPI_INT, 0, comm);
	int countHere = 0;
	countHere = keyCount(key, n, row);
	int totalCount;
	MPI_Reduce(&countHere, &totalCount, 1, MPI_INT, MPI_SUM, 0, comm);
	if(rank == 0){
		printf("Total count = %d\n", totalCount);
	}
	MPI_Finalize();
	return 0;
}