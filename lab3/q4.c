#include "mpi.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
int main(int argc, char *argv[])
{
	int rank,size,n;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	char a[100],b[100],str[100],str1[100];

	if(rank==0)
	{
		fprintf(stdout, "Enter the first string\n");
		fflush(stdout);
		scanf("%s",a);

		fprintf(stdout, "Enter the second string\n");
		fflush(stdout);
		scanf("%s",b);
	}

	n= strlen(a)/size;

	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	char c[2*n];
	MPI_Scatter(a,n,MPI_CHAR,str,n,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Scatter(b,n,MPI_CHAR,str1,n,MPI_CHAR,0,MPI_COMM_WORLD);
	int i;
	for(i=0;i<2*n;i++)
	{
		c[i] = i%2 ? str1[i/2] : str[i/2];
	}

	char str2[2*n];
	MPI_Gather(c,2*n,MPI_CHAR,str2,2*n,MPI_CHAR,0,MPI_COMM_WORLD);

	if(rank==0)
	{
		printf("%s\n",str2);
	}

	MPI_Finalize();
	return 0;
}









