#include <stdio.h>

int squares(int N)
{
	if(N<=0) return 0;
	return N*N+squares(N-1);
}

int main()
{
	int N;
	
	do
	{
		scanf("%d", &N);
		if(N == 0) break;
		printf("%d\n", squares(N));
	}while(N);

	return 0;
}
