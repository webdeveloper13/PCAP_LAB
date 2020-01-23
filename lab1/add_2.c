#include "mpi.h"
#include<stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int rank,size;
	//int key=0;
	int low,high;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0){
		low=2;
		high=49;
	}

	else{
		low=51;
		high=99;
	}

	for(int i=low;i<=high;i++){
		int key=0;
		for(int j=2;j<=i/2;j++){
			if(i%j==0)
			{
				key=1;
			    break;
			}
		}

		if(key==0){
			printf("%d\n",i);
		}
	}

	MPI_Finalize();
	
	return 0;
}