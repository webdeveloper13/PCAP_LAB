#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void square(int*a , int *t)
{
	int n = threadIdx.x, m=blockIdx.x, size=blockDim.x, size1=gridDim.x;
	int i= m*size+n;
	t[i]=1;
	//int final=0;
	for(int j=0;j<(m+1);j++)
		t[i]*=a[i];
}

int main(int argc, char const *argv[])
{
	int *a,*t,m,n,i,j;

	int *d_a, *d_t;

	printf("enter the value of m \n");
	scanf("%d",&m);
	printf("enter the value of n\n");
	scanf("%d",&n);

	int size= sizeof(int)*m*n;

	a=(int*)malloc(m*n*sizeof(int));
	t=(int*)malloc(m*n*sizeof(int));

	printf("enter the input matrix\n");

	for(i=0;i<m*n;i++)
		scanf("%d",&a[i]);

	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_t,size);

	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);

	square<<<m,n>>>(d_a,d_t);

	cudaMemcpy(t,d_t,size,cudaMemcpyDeviceToHost);

	printf("the result vector is :\n");

	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
			printf("%d\t",t[i*n+j] );

		printf("\n");
	}

	getchar();
	cudaFree(d_a);
	cudaFree(d_t);



	return 0;
}