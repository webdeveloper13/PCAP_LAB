#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void mat_add(int*a , int *b,int *c,int m)
{
	int i,index;
	int col_id=threadIdx.x;
	for(i=0;i<m;i++)
	{
		index=i*blockDim.x+col_id;
		c[index]=a[index]+b[index];
	}
}

int main(int argc, char const *argv[])
{
	int *a,*b,*c,m,n,i,j;

	int *d_a, *d_b,*d_c;

	printf("enter the value of m \n");
	scanf("%d",&m);
	printf("enter the value of n\n");
	scanf("%d",&n);

	int size= sizeof(int)*m*n;

	a=(int*)malloc(m*n*sizeof(int));
	b=(int*)malloc(m*n*sizeof(int));
	c=(int*)malloc(m*n*sizeof(int));
	printf("enter the input1 matrix\n");

	for(i=0;i<m*n;i++)
		scanf("%d",&a[i]);

	printf("enter the input2 matrix\n");

		for(i=0;i<m*n;i++)
			scanf("%d",&b[i]);

	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_b,size);
	cudaMalloc((void**)&d_c,size);
	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);
	mat_add<<<1,n>>>(d_a,d_b,d_c,m);

	cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);

	printf("the result vector is :\n");

	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
			printf("%d\t",c[i*n+j] );

		printf("\n");
	}

	getchar();
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);


	return 0;
}
