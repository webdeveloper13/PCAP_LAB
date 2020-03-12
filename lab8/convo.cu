#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
__global__ void convolution(int *I, int *M, int *O,int * w,int *mw){
	int WIDTH = * w;
	int MASK_WIDTH = *mw;
	int i = threadIdx.x;
	float op = 0;
	int si = i-(MASK_WIDTH/2);
	for(int j =0; j<MASK_WIDTH;j++){
		if(si+j >=0 && si+j < WIDTH){
			op+= I[si+j]*M[j];
		}
	}
	O[i]=op;
}

int main(int argc, char const *argv[]){
	int n,m,*d_w,*d_mw;
	printf("Enter the value n and m\n");
	scanf("%d",&n);
	scanf("%d",&m);
	int input[n],output[n],mask[m],*d_i,*d_m,*d_o;
	printf("Enter elements in 1st input array:\n");
	for(int i = 0;i<n;i++){
		scanf("%d",&input[i]);
	}
	printf("Enter elements in 2nd input array:\n");
	for(int i = 0;i<m;i++){
		scanf("%d",&mask[i]);
	}
	cudaMalloc((void **)&d_i,sizeof(int)*n);
	cudaMalloc((void **)&d_m,sizeof(int)*m);
	cudaMalloc((void **)&d_o,sizeof(int)*n);
	cudaMalloc((void **)&d_w,sizeof(int));
	cudaMalloc((void **)&d_mw,sizeof(int));
	cudaMemcpy(d_i,input,n*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(d_m,mask,m*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(d_w,&n,sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(d_mw,&m,sizeof(int),cudaMemcpyHostToDevice);
	convolution<<<1,n>>>(d_i,d_m,d_o,d_w,d_mw);
	cudaMemcpy(output,d_o,n*sizeof(int),cudaMemcpyDeviceToHost);
	for(int i = 0;i<n;i++){
		printf("%d ",output[i]);
	}
	cudaFree(d_i);
	cudaFree(d_m);
	cudaFree(d_o);
	return 0;
}
