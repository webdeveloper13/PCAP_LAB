#include "mpi.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
int main(int argc, char *argv[])
{
	int rank,size,len;
	char str[MAX];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);


	if(rank==0)
	{
		MPI_Status status;
		scanf("%s",str);
		len=strlen(str);
		MPI_Ssend(&len,1,MPI_INT,1,88,MPI_COMM_WORLD);
		MPI_Ssend(str,len+1,MPI_CHAR,1,99,MPI_COMM_WORLD);
		MPI_Recv(str,len+1,MPI_CHAR,1,111,MPI_COMM_WORLD,&status);
		//printf("After toggling the string we have:\n");
		
		fprintf(stdout,"toggled string is %s",str);
		

		fflush(stdout);
	}

	else
	{
		MPI_Status status;
		MPI_Recv(&len,1,MPI_INT,0,88,MPI_COMM_WORLD,&status);
		MPI_Recv(str,len+1,MPI_CHAR,0,99,MPI_COMM_WORLD,&status);

		for(int i=0;i<=len;i++)
		{
			if(str[i]>=65 && str[i]<=90){
				str[i]+=32;
			}

			else if(str[i]>=97 && str[i]<=122){
				str[i]-=32;
			}
		}

		MPI_Ssend(str,len+1,MPI_CHAR,0,111,MPI_COMM_WORLD);
		fflush(stdout);

	}

	MPI_Finalize();
	return 0;


}