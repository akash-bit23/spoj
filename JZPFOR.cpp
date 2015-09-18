#include <stdio.h>
#include <math.h>
#include <vector>

struct Point
{
	long x;
	long y;
	long z;
};

inline double dist(const Point & p1, const Point & p2)
{
	return sqrt( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z) );
}

int main()
{
	int n;
	scanf("%d", &n);

	std::vector<Point> points;
	points.resize(n);

	for(int i=0; i < n; ++i)
	{
		Point p;
		scanf("%d", &p.x);
		scanf("%d", &p.y);
		scanf("%d", &p.z);
		points[i] = p;
	}

	for(int i = 1; i < n; ++i)
	{
		printf("%.3f\n", dist(points[i], points[i-1]));
	}

	return 0;
}
