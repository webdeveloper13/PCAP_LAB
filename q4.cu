#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void sinw(float *a, float *b) {
	int i = blockIdx.x;
	b[i]=sinf(a[i]);
}

int main(void)
{
	int MAX = 10;
	float a[MAX], b[MAX];
	float *d_a, *d_b;
	int size = sizeof(int)*MAX;

	cudaMalloc((void**)&d_a, size);
	cudaMalloc((void**)&d_b, size);
	
	for (int i = 0; i < MAX; ++i)
	{
		a[i] = (3.14/4)*i;
		
	}

	
	printf("Array A:\n");
	for (int i = 0; i < MAX; ++i)
		printf("%f\t", a[i]);
	


	cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);
	
    sinw<<<MAX,1>>>(d_a, d_b);
	cudaMemcpy(&b, d_b, size, cudaMemcpyDeviceToHost);
	printf("\nFinal result:\n");
	for (int i = 0; i < MAX; ++i)
		printf("%f\t", b[i]);	
	
	printf("\n");


	cudaFree(d_a);
	cudaFree(d_b);
	
	return 0;
}
