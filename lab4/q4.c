#include <stdio.h>
#include "mpi.h"
#define comm MPI_COMM_WORLD

void errorDesc(int status){
	int class, len;
	MPI_Error_class(status, &class);
	printf("Error class = %d\n", class);
	fflush(stdout);
	char estring[MPI_MAX_ERROR_STRING];
	MPI_Error_string(status, estring, &len);
	printf("Error string = %s\n", estring);
	fflush(stdout);
}

int main(){
	int n, rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(comm, &n);
	MPI_Comm_rank(comm, &rank);
	MPI_Errhandler_set(comm, MPI_ERRORS_RETURN);
	int num = rank+1;
	int factNum;
	int status;
	status = MPI_Scan(&num, &factNum, 1, MPI_INT, MPI_PROD, comm);
	printf("%d-> Scan->\n", rank);
	fflush(stdout);
	errorDesc(status);
	int ans;
	status = MPI_Reduce(&factNum, &ans, 1, MPI_INT, MPI_SUM, 5, comm);
	printf("%d-> Reduce->\n", rank);
	fflush(stdout);
	errorDesc(status);
	if(rank == 0){
		printf("Final ans = %d\n", ans);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}