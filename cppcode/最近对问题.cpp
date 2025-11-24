#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>
using namespace std;

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    bool operator<(const Point &p) const
    {
        return x < p.x;
    }
};

double distance(const Point &p1, const Point &p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double bruteForce(const vector<Point> &points, int left, int right)
{
    double min_dist = numeric_limits<double>::max();
    for (int i = left; i <= right; ++i)
    {
        for (int j = i + 1; j <= right; ++j)
        {
            min_dist = min(min_dist, distance(points[i], points[j]));
        }
    }
    return min_dist;
}

double stripClosest(vector<Point> &strip, double d)
{
    double min_dist = d;
    sort(strip.begin(), strip.end(), [](const Point &p1, const Point &p2)
         { return p1.y < p2.y; });
    for (int i = 0; i < strip.size(); ++i)
    {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min_dist; ++j)
        {
            min_dist = min(min_dist, distance(strip[i], strip[j]));
        }
    }
    return min_dist;
}

double closestUtil(vector<Point> &px, int left, int right)
{
    if (right - left <= 3)
    {
        return bruteForce(px, left, right);
    }
    int mid = (left + right) / 2;
    Point midPoint = px[mid];
    double dl = closestUtil(px, left, mid);
    double dr = closestUtil(px, mid + 1, right);
    double d = min(dl, dr);
    vector<Point> strip;
    for (int i = left; i <= right; ++i)
    {
        if (abs(px[i].x - midPoint.x) < d)
        {
            strip.push_back(px[i]);
        }
    }
    return min(d, stripClosest(strip, d));
}

double closest(vector<Point> &px)
{
    sort(px.begin(), px.end(), [](const Point &p1, const Point &p2)
         { return p1.x < p2.x; });
    return closestUtil(px, 0, px.size() - 1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--)
    {
        int m;
        cin >> m;
        vector<Point> points(m);
        for (int i = 0; i < m; ++i)
        {
            cin >> points[i].x >> points[i].y;
        }
        double result = closest(points);
        cout << fixed << setprecision(4) << result << '\n';
    }
    return 0;
}

/*上面的分治法太高级了，这道题的要求时空限制不高，直接暴力法即可

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>
using namespace std;

struct Point { double x, y; };

double closestPair(vector<Point>& points) {
    double min_dist = numeric_limits<double>::max();
    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            double dx = points[i].x - points[j].x;
            double dy = points[i].y - points[j].y;
            min_dist = min(min_dist, dx*dx + dy*dy); // 用平方距离比较
        }
    }
    return sqrt(min_dist); // 最后再开方
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        int m;
        cin >> m;
        vector<Point> points(m);
        for (int i = 0; i < m; ++i) {
            cin >> points[i].x >> points[i].y;
        }
        cout << fixed << setprecision(4) << closestPair(points) << '\n';
    }
    return 0;
}
*/