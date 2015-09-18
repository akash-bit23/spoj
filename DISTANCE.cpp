#include <iostream>
#include <chrono>
#include <stdio.h>
#include <sstream>
#include <string>
#include <string.h>

static const int MAX_DIMENSIONS = 6;
static const int MAX_POINTS = 1000000;
int extremumCount = 0;

struct Point
{
	int val[MAX_DIMENSIONS];
	int extremum[1 << MAX_DIMENSIONS];
};


std::string inputStr;
int N = 0;
int d = 0;
int size = 0;
Point points[MAX_POINTS];
int extremums[1 << MAX_DIMENSIONS];	
bool signs[MAX_DIMENSIONS << MAX_DIMENSIONS];


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

void readInput()
{
	std::cin >> N >> d;
	size = N*d;
	extremumCount = 1<<d;

	static const int BUFFER_SIZE = 1024*1024;
	char buf[BUFFER_SIZE];
	while(std::cin.good()) 
	{
		std::cin.read(buf, BUFFER_SIZE);
		inputStr.append(buf, std::cin.gcount());
	}
}

void readPoints()
{
	char * input = (char*)inputStr.data();
	
	for(int i = 0; i < N; ++i) 
	{
		Point & point = points[i];
		for(int k = 0; k < d; ++k)
		{
			point.val[k] = strtol(input, &input, 10);

			for(int e = 0; e < extremumCount; ++e)
			{
				point.extremum[e] += point.val[k] * ((e >> k) % 2 ? 1 : -1);
			}
		}

		for(int e = 0; e < extremumCount; ++e)
		{
			if(i == 0 || point.extremum[e] > extremums[e])
			{
				extremums[e] = point.extremum[e];
			}
		}
	}
}

void calcGoodPoints()
{
	int offset = 0;
	for(int i = 0; i < N; ++i)
	{
		for(int e = 0; e < extremumCount; ++e)
		{
			if(points[i].extremum[e] == extremums[e])
			{
				points[offset] = points[i];
				++offset;
				break;
			}
		}
	}
	N = offset;
}

int calcMaxDistance()
{
	int maxDistance = 0;
	Point * end = points + N;
	for(Point * p1 = points; p1 != end; ++p1)
	{
		for(Point * p2 = p1; p2 != end; ++p2)
		{
			int distance = calcDistance(p1->val, p2->val, d);
			if(distance > maxDistance)
			{
				maxDistance = distance;
			}
		}
	}
	return maxDistance;
}

int main()
{
	auto start = std::chrono::system_clock::now();

	memset(points, 0, MAX_POINTS * sizeof(Point));
//	std::cout << "Init done, elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;

	readInput();
//	std::cout << "Read done, elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;

	readPoints();
//	std::cout << "Read points done, elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;

	calcGoodPoints();
//	std::cout << "Good points(" << N << "), elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;

	std::cout << calcMaxDistance() << std::endl;

//	std::cout << "Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms" << std::endl;

	return 0;
}
