#include <iostream>
#include <chrono>
#include <stdio.h>
#include <sstream>
#include <string>
#include <string.h>

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

int main()
{
	auto start = std::chrono::system_clock::now();

	int N;
	int d;
	std::cin >> N >> d;
	int size = N*d;
	int * points = new int[size];

	int extremums[1 << MAX_DIMENSIONS];	
	int extremumCount = 1 << d;

	int signs[extremumCount * d];
	int s = 0;
	for(int e = 0; e < extremumCount; ++e)
	{
		for(int k = 0; k < d; ++k)
		{
			signs[s] = ((e >> k) % 2 ? 1 : -1);
			++s;
		}
	}

	#ifdef DEBUG
	std::cout << "Init done, elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;
	#endif

	std::string input;
	static const int BUFFER_SIZE = 1024*1024;
	char buf[BUFFER_SIZE];
	while(std::cin.good()) 
	{
		std::cin.read(buf, BUFFER_SIZE);
		input.append(buf, std::cin.gcount());
	}
	#ifdef DEBUG
	std::cout << "Read done(" << size/d << "), elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;
	#endif

	char * inputStr = (char*)input.data();
	
	int out = 0;
	for(int i = 0; i < size; i += d) 
	{
		for(int k = 0; k < d; ++k)
		{
			points[out+k] = strtol(inputStr, &inputStr, 10);
		}
		bool good = false;
		int s = 0;
		for(int e = 0; e < extremumCount; ++e)
		{
			int extremum = 0;
			for(int k = 0; k < d; ++k)
			{
				extremum += points[out+k]*signs[s];
				++s;
			}
			if(i == 0 || extremum >= extremums[e])
			{
				extremums[e] = extremum;
				good = true;
			}
		}
		if(good)
		{
			out += d;
		}
	}
	size = out;

	#ifdef DEBUG
	std::cout << "Read points done(" << size/d << "), elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;
	#endif

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
	std::cout << maxDistance << std::endl;

	#ifdef DEBUG
	std::cout << "Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;
	#endif

	return 0;
}
