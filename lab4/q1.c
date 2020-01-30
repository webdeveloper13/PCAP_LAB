#include <stdio.h>
#include "mpi.h"
#define MCW MPI_COMM_WORLD

int main(){
	int n, rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MCW, &n);
	MPI_Comm_rank(MCW, &rank);
	int num = rank+1;
	int factNum,sum;
	MPI_Scan(&num, &factNum, 1, MPI_INT, MPI_PROD, MCW);
	
	int ans;
	MPI_Scan(&factNum,&sum,1,MPI_INT,MPI_SUM,MCW);
	if(rank == n-1){
		printf("Final ans = %d\n", sum);
	}
	MPI_Finalize();
	return 0;
}