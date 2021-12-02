#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;

float mindist = INT_MAX;
int ansa = 0, ansb = 0;

struct point
{
    int id;
    int x;
    int y;
};

bool sort_points(point i, point j) { return (i.x < j.x); }

void upd_ans(const point& a, const point& b)
{
    int katet1 = a.x - b.x;
    int katet2 = a.y - b.y;
    float dist = sqrt(katet1 * katet1 + katet2 * katet2);
    if (dist < mindist)
    {
        mindist = dist;
        ansa = a.id;
        ansb = b.id;
    }
}

void rec(vector<point> points, int left, int right, int mid)
{
    if (right - left <= 3)
    {
        for (int i = left; i <= right; ++i)
            for (int j = i + 1; j <= right; ++j)
                upd_ans(points[i], points[j]);
        return;
    }

    point* t = new point[points.size()];
    int midx = points[mid].x;
    int tsz = 0;
    for (int i = left; i <= right; ++i)
        if (abs(points[i].x - midx) < mindist)
        {
            for (int j = tsz - 1; j >= 0 && (points[i].y - t[j].y < mindist); j--)
            {
                upd_ans(points[i], t[j]);
            }
            t[tsz++] = points[i];
        }
}

void DAC_sort(vector<point> points, int left, int right)
{
    if (left >= right) return;
    int mid = (left + right) / 2;
    DAC_sort(points, left, mid);
    DAC_sort(points, mid + 1, right);
    rec(points, left, right, mid);
}

void rough_sort(vector<point> points)
{
    float min = INT_MAX; int ind1 = 0, ind2 = 0;
    for (size_t i = 0; i < points.size() - 1; i++)
    {
        for (size_t j = i + 1; j < points.size(); j++)
        {
            int katet1 = points[i].x - points[j].x;
            int katet2 = points[i].y - points[j].y;
            float dist = sqrt(katet1 * katet1 + katet2 * katet2);
            if (dist < min)
            {
                min = dist;
                ind1 = i;
                ind2 = j;
            }
        }
    }

    cout << "Кратчайшие расстояние между точками " << min << " между точками "
        << '(' << points[ind1].x << ',' << points[ind1].y << ") и ("
        << points[ind2].x << ',' << points[ind2].y << ')';
}

void main()
{
    setlocale(LC_ALL, "");
    size_t n;
    ifstream ist("in.txt");
    ist >> n;
    vector<point> points;
    for (size_t i = 0; i < n; i++)
    {
        point newPoint;
        newPoint.id = i;
        ist >> newPoint.x;
        ist >> newPoint.y;
        points.push_back(newPoint);
    }
    sort(points.begin(), points.end(), sort_points);
    auto t1 = high_resolution_clock::now();
    rough_sort(points);
    auto t2 = high_resolution_clock::now();
    cout << "\nЗатраченное время: " << duration_cast<microseconds>(t2 - t1).count() / 1000.0f;
    t1 = high_resolution_clock::now();
    DAC_sort(points, 0, n - 1);
    t2 = high_resolution_clock::now();
    

    int point_a = 0, point_b = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (ansa == points[i].id)
            point_a = i;
        else if (ansb == points[i].id)
            point_b = i;
    }
    cout << "\nКратчайшие расстояние между точками " << mindist << " между точками "
        << '(' << points[point_a].x << ',' << points[point_a].y << ") и ("
        << points[point_b].x << ',' << points[point_b].y << ')';
    cout << "\nЗатраченное время: " << duration_cast<microseconds>(t2 - t1).count() / 1000.0f;
}