#include <iostream>
#include <chrono>
#include <stdio.h>
#include <sstream>
#include <string>
#include <string.h>

static int parseint()
{
    int c, n;

    bool minus = getchar() == '-';

    n = getchar() - '0';
    while ((c = getchar()) >= '0')
        n = 10*n + c-'0';

    if(minus) n = -n;

    return n;
}

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

	char * inputStr = (char*)input.data();
	
	for(int i = 0; i < size; i += d) 
	{
		for(int k = 0; k < d; ++k)
		{
			points[i+k] = strtol(inputStr, &inputStr, 10);
		}
		for(int e = 0; e < (1<<d); ++e)
		{
			int extremum = 0;
			for(int k = 0; k < d; ++k)
			{
				extremum += points[i+k] * ((e >> k) % 2 ? 1 : -1);
			}
			if(i == 0 || extremum > extremums[e])
			{
				extremums[e] = extremum;
			}
		}
	}

//	std::cout << "Read done, elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;

	int * goodPoints = new int[d<<MAX_DIMENSIONS];
	int goodPointCount = 0;
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
				memcpy(goodPoints + goodPointCount * d, points + i, d * sizeof(int));
				++goodPointCount;
				break;
			}
		}
	}

//	std::cout << "good points " << goodPointCount << " / " << N << std::endl;

	int maxDistance = 0;
	int * end = goodPoints + goodPointCount*d;
	for(int * p1 = goodPoints; p1 != end; p1 += d)
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
	delete[] goodPoints;
	std::cout << maxDistance << std::endl;

//	std::cout << "Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;

	return 0;
}
