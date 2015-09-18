#include <iostream>
#include <chrono>

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

int main()
{
	auto start = std::chrono::system_clock::now();

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
	int best1 = 0;
	int best2 = 0;
	for(int * p1 = points; p1 != end; p1 += d)
	{
		for(int * p2 = p1; p2 != end; p2 += d)
		{
			int distance = calcDistance(p1, p2, d);
			if(distance > maxDistance)
			{
				maxDistance = distance;
				best1 = int(p1-points)/d;
				best2 = int(p2-points)/d;
			}
		}
	}
	delete[] points;
	std::cout << maxDistance << std::endl;
	std::cout << "between " << best1 << " " << best2 << std::endl;

	std::cout << "Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;
	return 0;
}
