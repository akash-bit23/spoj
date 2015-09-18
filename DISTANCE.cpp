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

	std::string input;
	static const int BUFFER_SIZE = 1024*1024;
	char buf[BUFFER_SIZE];
	while(std::cin.good()) 
	{
		std::cin.read(buf, BUFFER_SIZE);
		input.append(buf, std::cin.gcount());
	}
//	std::cout << "Read done(" << size/d << "), elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;

	char * inputStr = (char*)input.data();
	
	int out = 0;
	for(int i = 0; i < size; i += d) 
	{
		for(int k = 0; k < d; ++k)
		{
			points[out+k] = strtol(inputStr, &inputStr, 10);
		}
		bool notgood = true;
		for(int e = 0; e < (1<<d); ++e)
		{
			int extremum = 0;
			for(int k = 0; k < d; ++k)
			{
				extremum += points[out+k] * ((e >> k) % 2 ? 1 : -1);
			}
			if(i == 0 || extremum >= extremums[e])
			{
				extremums[e] = extremum;
				notgood = false;
			}
		}
		if(!notgood)
		{
			out += d;
		}
	}
	size = out;

//	std::cout << "Read points done(" << size/d << "), elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;

	int goodSize = 0;
	for(int i = 0; i < size; i += d)
	{
		for(int e = 0; e < (1<<d); ++e)
		{
			int extremum = 0;
			for(int k = 0; k < d; ++k)
			{
				extremum += points[i+k] * ((e >> k) % 2 ? 1 : -1);
			}
			if(extremum == extremums[e])
			{
				memcpy(points + goodSize, points + i, d * sizeof(int));
				goodSize += d;
				break;
			}
		}
	}
	size = goodSize;

//	std::cout << "Good points done(" << size/d << "), elapsed " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;

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

//	std::cout << "Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;

	return 0;
}
