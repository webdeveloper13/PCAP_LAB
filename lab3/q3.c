#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20

int checkvowels(char str[], int arrsize) 
{
	int sum = 0;
	for(int i =0; i < arrsize; i++) {
		if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
			sum++;
	}	
	return (arrsize-sum);
}

int main(int argc, char *argv[])
{
	int rank, size;
	char word[MAX], a[MAX], b[MAX];
	int len = 0, N = 0;
	int c = 0, sum = 0, b2[MAX];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;

	if(rank == 0) {
		N = size;
		fprintf(stdout, "Enter string: \n");
		fgets(word, MAX, stdin);
		len = strlen(word)/N;
	}

	MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(word, len, MPI_CHAR, b, len, MPI_CHAR, 0, MPI_COMM_WORLD);
	c = checkvowels(b, len);
	MPI_Gather(&c, 1, MPI_INT, b2, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0) {
		fprintf(stdout, "\nThe non vowels by each process are: \n");
		fflush(stdout);
		for (int i = 0; i < N; i++)
			printf("%d\t",b2[i]);
		for (int i = 0; i < N; i++)
		{
			sum += b2[i];
		}
		printf("\n%d\n", sum);
	}

	MPI_Finalize();
	return 0;
}