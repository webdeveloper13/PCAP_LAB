#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void add(int *a, int *b, int *c) {
	int i = blockIdx.x;
	c[i] = a[i] + b[i];
}

__global__ void add2(int *a, int *b, int *c) {
	int i = threadIdx.x;
	c[i] = a[i] + b[i];
}

__global__ void add3(int *a, int *b, int *c, int MAX) {
	int i = blockIdx.x*blockDim.x + threadIdx.x;
	
	if (i<MAX)
		c[i] = a[i] + b[i];
	
}

int main(void)
{
	int MAX = 10;
	int a[MAX], b[MAX], c[MAX];
	int *d_a, *d_b, *d_c;
	int size = sizeof(int)*MAX;

	cudaMalloc((void**)&d_a, size);
	cudaMalloc((void**)&d_b, size);
	cudaMalloc((void**)&d_c, size);

	for (int i = 0; i < MAX; ++i)
	{
		a[i] = i+10;
		b[i] = i*20;
	}

	printf("Array A:\n");
	for (int i = 0; i < MAX; ++i)
		printf("%d\t", a[i]);
	printf("\nArray B:\n");
	for (int i = 0; i < MAX; ++i)
		printf("%d\t", b[i]);


	cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);

	//No of blocks is MAX, No of threads in each block is 1
	add<<<MAX,1>>>(d_a, d_b, d_c);
	cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);
	printf("\nOutput 1:\n");
	for (int i = 0; i < MAX; ++i)
		printf("%d\t", c[i]);	
	add2<<<1, MAX>>>(d_a, d_b, d_c);
	cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);
	printf("\nOutput 2:\n");
	for (int i = 0; i < MAX; ++i)
		printf("%d\t", c[i]);
	add3<<<ceil(MAX/256), 256>>>(d_a, d_b, d_c, MAX);
	cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);
	printf("\nOutput 3:\n");
	for (int i = 0; i < MAX; ++i)
		printf("%d\t", c[i]);
	printf("\n");


	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}
