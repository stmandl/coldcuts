#include <bits/stdc++.h>
using namespace std;

struct Point
{
	float x;
	float y;
	float dist(const Point& other) const
	{
		float d1 = other.x - x;
		float d2 = other.y - y;
		return sqrtf64x(d1 * d1 + d2 * d2);
	}
	Point(float x_, float y_) : x(x_), y(y_){};
	bool operator<(const Point& other) const
	{
		return x < other.x || (x == other.x && y < other.y);
	}
	bool operator==(const Point& other) const
	{
		return x == other.x && y == other.y;
	}
};

void solve(vector<Point> &points /*,
		   int32_t min_x,
		   int32_t max_x,
		   int32_t min_y,
		   int32_t max_y*/)
{
	sort(points.begin(), points.end());
	float closest_distance_so_far = numeric_limits<float>::max();
	int closest_p1 = -1;
	int closest_p2 = -1;
	for (int i1 = 0; i1 < points.size() - 1; i1++)
	{
		const Point& p1 = points[i1];
		for (int i2 = i1 + 1; i2 < points.size(); i2++)
		{
			const Point& p2 = points[i2];
			if ((p2.x - p1.x) > closest_distance_so_far)
			{
			 	break;
			}
			float dist = p1.dist(p2);
			if (dist < closest_distance_so_far)
			{
				closest_distance_so_far = dist;
				closest_p1 = i1;
				closest_p2 = i2;
			}
		}
	}
	assert(closest_p1 != -1);
	assert(closest_p2 != -1);
	const Point &p1 = points[closest_p1];
	const Point &p2 = points[closest_p2];
	cout << std::fixed << std::setprecision(2) << p1.x<< " " << p1.y;
	cout << " " << p2.x << " " << p2.y << endl;
}

int main()
{
	for (;;)
	{
		int32_t N;
		cin >> N;
		if (N < 2)
		{
			return 0;
		}
		vector<Point> points;
		points.reserve(N);
		// float min_x = numeric_limits<float>::max();
		// float max_x = numeric_limits<float>::min();
		// float min_y = numeric_limits<float>::max();
		// float max_y = numeric_limits<float>::min();
		for (int i = 0; i < N; ++i)
		{
			float x, y;
			cin >> x;
			cin >> y;
			// if (x < min_x)
			// 	min_x = x;
			// if (y < min_y)
			// 	min_y = y;
			// if (x > max_x)
			// 	max_x = x;
			// if (y > max_y)
			// 	max_y = y;
			points.emplace_back(x, y);			
		}
		solve(points /*, min_x, max_x, min_y, max_y */);
	}
}
