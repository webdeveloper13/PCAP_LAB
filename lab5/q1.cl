__kernel void q1 (__global int *A, __global int *C)
{
	int i = get_global_id(0);
	int oct=0;
	int j=1;

	while(A[i]!=0)
	{
		oct += (A[i]%8)*j;
		A[i]/=8;
		j*=10;
	}

	C[i]=oct;

}