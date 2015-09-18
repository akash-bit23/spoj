#include <stdio.h>

int main() 
{
	int T;
	scanf("%d", &T);

	for(int i = 0; i < T; ++i) 
	{
		int w;
		int b;
		scanf("%d", &w);
		scanf("%d", &b);
		printf("%.6f\n", (float)(b % 2));
	}

	return 0;
}