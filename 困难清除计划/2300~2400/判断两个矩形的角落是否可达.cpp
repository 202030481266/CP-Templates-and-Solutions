#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

struct Circle {
    double x, y, r;
};

struct Point {
    double x, y;
};

double distance(double x1, double y1, double x2, double y2) { // 求解距离
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

std::vector<Point> line_circle_intersections(double x1, double y1, double x2, double y2, double cx, double cy, double r) {
    std::vector<Point> intersections;
    double dx = x2 - x1;
    double dy = y2 - y1;
    double a = dx * dx + dy * dy;
    double b = 2 * (dx * (x1 - cx) + dy * (y1 - cy));
    double c = (x1 - cx) * (x1 - cx) + (y1 - cy) * (y1 - cy) - r * r;
    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        double t2 = (-b + std::sqrt(discriminant)) / (2 * a);
        if (t1 >= 0 && t1 <= 1) {
            intersections.push_back({x1 + t1 * dx, y1 + t1 * dy});
        }
        if (t2 >= 0 && t2 <= 1 && t2 != t1) {
            intersections.push_back({x1 + t2 * dx, y1 + t2 * dy});
        }
    }
    return intersections;
}

std::vector<int> circle_rectangle_intersecting_sides(const Circle& circle, double X, double Y) {
    std::vector<int> intersecting_sides;
    double xi = circle.x, yi = circle.y, ri = circle.r;

    // Check if the circle is completely outside the rectangle
    if (xi + ri < 0 || xi - ri > X || yi + ri < 0 || yi - ri > Y) {
        return intersecting_sides;
    }

    // Check for intersections with each side of the rectangle
    std::vector<std::pair<Point, Point>> sides = {
        {{0, 0}, {X, 0}}, {{X, 0}, {X, Y}}, {{X, Y}, {0, Y}}, {{0, Y}, {0, 0}}
    };

    std::vector<int> side_ids = {2, 4, 3, 1}; // Corresponding side IDs

    for (size_t i = 0; i < sides.size(); ++i) {
        auto [p1, p2] = sides[i];
        double x1 = p1.x, y1 = p1.y;
        double x2 = p2.x, y2 = p2.y;

        auto side_intersections = line_circle_intersections(x1, y1, x2, y2, xi, yi, ri);
        if (!side_intersections.empty()) {
            intersecting_sides.push_back(side_ids[i]);
        }
    }

    return intersecting_sides;
}

std::vector<Point> circle_intersections(double x1, double y1, double r1, double x2, double y2, double r2) {
    std::vector<Point> intersections;
    double d = distance(x1, y1, x2, y2);
    if (d > r1 + r2 || d < std::abs(r1 - r2)) return intersections;

    double a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
    double h = std::sqrt(r1 * r1 - a * a);
    double x0 = x1 + a * (x2 - x1) / d;
    double y0 = y1 + a * (y2 - y1) / d;
    double rx = -(y2 - y1) * h / d;
    double ry = (x2 - x1) * h / d;

    intersections.push_back({x0 + rx, y0 + ry});
    intersections.push_back({x0 - rx, y0 - ry});
    return intersections;
}

bool is_inside_rectangle(double x, double y, double X, double Y) {
    return x >= 0 && x <= X && y >= 0 && y <= Y;
}

const int F[] = {3, 9, 6, 12};
// 连通性问题
class Solution {
public:
    bool canReachCorner(int X, int Y, vector<vector<int>>& circles) {
        vector<Circle> a;
        for (auto& c : circles) a.push_back(Circle{1.0*c[0], 1.0*c[1], 1.0*c[2]});
        vector<int> g;
        for (int i = 0; i < a.size(); ++i) {
            // 判断两个点是否在圆的内部
            if ((a[i].x)*(a[i].x)+(a[i].y)*(a[i].y) <= a[i].r*a[i].r || (a[i].x-X)*(a[i].x-X)+(a[i].y-Y)*(a[i].y-Y)<=a[i].r*a[i].r) {
                return false;
            }
            auto intersecting_sides = circle_rectangle_intersecting_sides(a[i], X, Y);
            int status = 0;
            for (int v : intersecting_sides) {
                status |= (1<<(v-1));
            }
            for (int k = 0; k < i; ++k) {
                auto intersections = circle_intersections(a[k].x, a[k].y, a[k].r, a[i].x, a[i].y, a[i].r);
                bool intersect_inside_rectangle = false;
                for (const auto& p : intersections) {
                    // cout << p.x << ' ' << p.y << endl;
                    if (is_inside_rectangle(p.x, p.y, X, Y)) { // 判断交点是否在矩形内部，因为必须是内部连通而不是外部连通
                        intersect_inside_rectangle = true;
                        break;
                    }
                }
                if (intersect_inside_rectangle) {
                    status |= g[k];
                }
            }
            g.push_back(status);
            // check
            for (int f : F) if ((status & f) == f) return false;
        }
        return true;
    }
};