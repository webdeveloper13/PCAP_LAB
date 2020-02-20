#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void add(int *a, int *b, int *alpha) {
	int i = blockIdx.x;
	b[i]=*alpha*a[i]+b[i];
}


int main(void)
{
	int MAX = 10;
	int a[MAX], b[MAX], alpha;
	int *d_a, *d_b, *d_c;
	int size = sizeof(int)*MAX;

	cudaMalloc((void**)&d_a, size);
	cudaMalloc((void**)&d_b, size);
	cudaMalloc((void**)&d_c, sizeof(int));

	for (int i = 0; i < MAX; ++i)
	{
		a[i] = i+10;
		b[i] = i*20;
	}

	alpha=2;

	printf("Array A:\n");
	for (int i = 0; i < MAX; ++i)
		printf("%d\t", a[i]);
	printf("\nArray B:\n");
	for (int i = 0; i < MAX; ++i)
		printf("%d\t", b[i]);


	cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_c, &alpha, sizeof(int), cudaMemcpyHostToDevice);
    add<<<MAX,1>>>(d_a, d_b, d_c);
	cudaMemcpy(&b, d_b, size, cudaMemcpyDeviceToHost);
	printf("\nFinal Result:\n");
	for (int i = 0; i < MAX; ++i)
		printf("%d\t", b[i]);	
	
	printf("\n");


	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}
