#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int x, y, z;
};

int gcd(int a, int b) {
    if (b == 0) return abs(a);
    return gcd(b, a % b);
}

int maxPointsOnLine(vector<Point>& points) {
    int n = points.size();
    if (n <= 2) return n;

    int maxPoints = 2;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dx = points[j].x - points[i].x;
            int dy = points[j].y - points[i].y;
            int dz = points[j].z - points[i].z;

            int g = gcd(gcd(dx, dy), dz);
            dx /= g; dy /= g; dz /= g;

            int count = 0;
            for (int k = 0; k < n; k++) {
                int dx2 = points[k].x - points[i].x;
                int dy2 = points[k].y - points[i].y;
                int dz2 = points[k].z - points[i].z;

                if (dx2 * dy == dy2 * dx && dy2 * dz == dz2 * dy && dx2 * dz == dz2 * dx) {
                    count++;
                }
            }
            maxPoints = max(maxPoints, count);
        }
    }

    return maxPoints;
}

int main() {
    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y >> points[i].z;
    }

    int maxCollinearPoints = maxPointsOnLine(points);
    cout << n - maxCollinearPoints << endl;

    return 0;
}
