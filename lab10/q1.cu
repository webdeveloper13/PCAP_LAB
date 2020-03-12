#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<cuda_runtime.h>

__global__ void matmul(int *a,int *b,int *c,int WIDTH){
	int rowa=blockIdx.y*blockDim.y+threadIdx.y;
	int colb=blockIdx.x*blockDim.x+threadIdx.x;
	int sum=0;
	for(int i=0;i<WIDTH;i++)
		sum+=a[rowa*WIDTH+i]*b[i*WIDTH+colb];
	c[rowa*WIDTH+colb]=sum;
}

int main(){
	int WIDTH,BLOCK_WIDTH;
	int *matA,*matB,*matSum;
	int *da,*db,*dc;
	printf("enter width of matrix\n");
	scanf("%d",&WIDTH);
	BLOCK_WIDTH=WIDTH/2;
	printf("Enter elements of matrix A\n");
	matA=(int*)malloc(sizeof(int)*WIDTH*WIDTH);
	for(int i=0;i<WIDTH*WIDTH;i++){
		scanf("%d",&matA[i]);
	}
	printf("Enter elements of matrix B\n");
	matB=(int*)malloc(sizeof(int)*WIDTH*WIDTH);
	for(int i=0;i<WIDTH*WIDTH;i++){
		scanf("%d",&matB[i]);
	}
	matSum=(int*)malloc(sizeof(int)*WIDTH*WIDTH);
	cudaMalloc((void**)&da,sizeof(int)*WIDTH*WIDTH);
	cudaMalloc((void**)&db,sizeof(int)*WIDTH*WIDTH);
	cudaMalloc((void**)&dc,sizeof(int)*WIDTH*WIDTH);
	cudaMemcpy(da,matA,sizeof(int)*WIDTH*WIDTH,cudaMemcpyHostToDevice);
	cudaMemcpy(db,matB,sizeof(int)*WIDTH*WIDTH,cudaMemcpyHostToDevice);
	int NumBlocks=WIDTH/BLOCK_WIDTH;
	dim3 grid_conf(NumBlocks,NumBlocks);
	dim3 block_conf(BLOCK_WIDTH,BLOCK_WIDTH);
	matmul<<<grid_conf,block_conf>>>(da,db,dc,WIDTH);
	cudaMemcpy(matSum,dc,sizeof(int)*WIDTH*WIDTH,cudaMemcpyDeviceToHost);
	int n=WIDTH;
	int m=WIDTH;
	printf("Result: \n");
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			printf("%d ",matSum[i*n+j]);
		}
		printf("\n");
	}
	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
	free(matA);
	free(matB);
	free(matSum);
	return 0;
}
