__kernel void onecomp (__global int *A, __global int *C )
{
	int i = get_global_id(0);
	int temp= 0, x= 1;
	while(A[i] != 0)
	{
		temp = A[i]%10;
		if (temp) temp = 0;
		else temp = 1;
		
		C[i] += (temp*x);
		
		x *= 10;
		A[i] /= 10;
	}
