#include<stdio.h>
#include<stdlib.h>

__global__ void transpose(int *a,int *t)
{
  int id=blockIdx.x*blockDim.x+threadIdx.x;
  int flag=0,comp,j=1;  
  if(blockIdx.x==0 || (blockIdx.x+1)%gridDim.x == 0 || threadIdx.x==0 || (threadIdx.x+1)%blockDim.x==0)
    flag=1;
  if(!flag)
    {
    	t[id]=0;
        while(a[id]!=0){
			comp=a[id]%2;
			if(comp)
				comp=0;
			else
				comp=1;
			t[id]+=(comp*j);
			j*=10;
			a[id]/=2;
		}

    }
 else
 {
     t[id]=a[id];
 }
}

int main(void)
{
	int *t,m,n,i,j;
	int *d_a,*d_t,*d_m;
  m=4;
	n=4;
  int a[]={1,2,3,4,5,5,8,8,9,4,10,12,13,14,15,16};
  int size=sizeof(int)*m*n;
	t=(int*)malloc(m*n*sizeof(int));
	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_t,size);
	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	transpose<<<m,n>>>(d_a,d_t);
	cudaMemcpy(t,d_t,size,cudaMemcpyDeviceToHost);
	printf("result vector is:\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",t[i*n+j] );
		}
		printf("\n");
	}
	cudaFree(d_a);
	cudaFree(d_t);
	return 0;
}