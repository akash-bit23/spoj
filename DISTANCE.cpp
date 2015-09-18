#include <iostream>
#include <chrono>

static const int MAX_DIMENSIONS = 6;

inline int calcDistance(int * p1, int * p2, int d)
{
	int distance = 0;
	int * end = p1 + d;
	while(p1 != end)
	{
		distance += std::abs(*p1 - *p2);
		++p1;
		++p2;
	}
	return distance;
}

int brute()
{
	int N;
	int d;
	std::cin >> N >> d;
	int size = N*d;
	int * points = new int[size];
	for(int i = 0; i < size; ++i) 
	{
		std::cin >> points[i];
	}

	int maxDistance = 0;
	int * end = points + size;
	for(int * p1 = points; p1 != end; p1 += d)
	{
		for(int * p2 = p1; p2 != end; p2 += d)
		{
			int distance = calcDistance(p1, p2, d);
			if(distance > maxDistance)
			{
				maxDistance = distance;
			}
		}
	}
	delete[] points;
	return maxDistance;
}

int calcCorners()
{
	int N;
	int d;
	std::cin >> N >> d;
	int size = N*d;
	int * points = new int[size];

	int extremums[MAX_DIMENSIONS];	
	
	for(int i = 0; i < size; i += d) 
	{
		for(int k = 0; k < d; ++k)
		{
			std::cin >> points[i+k];
		}
		for(int e = 0; e < d; ++e)
		{
			
		}
	}

	int maxDistance = 0;
	int * end = points + size;
	for(int * p1 = points; p1 != end; p1 += d)
	{
		for(int * p2 = p1; p2 != end; p2 += d)
		{
			int distance = calcDistance(p1, p2, d);
			if(distance > maxDistance)
			{
				maxDistance = distance;
			}
		}
	}
	delete[] points;
	return maxDistance;
}

int main()
{
	auto start = std::chrono::system_clock::now();

	std::cout << calcCorners() << std::endl;

	std::cout << "Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;

	return 0;
}
