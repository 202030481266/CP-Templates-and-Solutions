#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;

static constexpr double inf = 2e9;
static constexpr int maxn = 2e5;
static constexpr double eps = 1e-7;

struct Line {
    double k, b;
    int _x1, _y1, _x2, _y2;
    Line() {}
    Line(int x1, int y1, int x2, int y2): _x1(x1), _y1(y1), _x2(x2), _y2(y2) {
        if (x1 == x2) {
            k = inf;
            b = x1;
        }
        else {
            k = (double)(y2 - y1) / (x2 - x1);
            if (y2 == y1) {
                b = y2;
            }
            else {
                b = (double)(x2 * (y2 - y1) - y2 * (x2 - x1)) / (y2 - y1);
            }
        }
    }
    int getLen() {
        return (_x2 - _x1) * (_x2 - _x1) + (_y2 - _y1) * (_y2 - _y1); 
    }
} lines[maxn];

int m = 0;

bool equal(double a, double b) {
    return fabs(a - b) < eps;
}

static constexpr int maxv = 4e6;
int len[maxv << 1];

class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        ranges::sort(points);
        m = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                lines[m++] = Line(points[i][0], points[i][1], points[j][0], points[j][1]);
            }
        }
        sort(lines, lines + m, [&](const Line& line1, const Line& line2) {
            return equal(line1.k, line2.k) ? line1.b < line2.b : line1.k < line2.k;
        });
        int p = 0, ans = 0, sub = 0; 
        vector<vector<int>> group;
        auto cal = [&](int lo, int up) {
            vector<int> tmp;
            for (int k = lo; k < up; ++k) {
                len[lines[k].getLen()] = 0;
                tmp.push_back(lines[k].getLen());
            }
            group.push_back(tmp);
        };
        while (p < m) {
            int i = p + 1;
            while (i < m && equal(lines[p].k, lines[i].k)) ++i;
            int l = p, flag = 1; 
            group.clear();
            for (int j = p; j < i; ++j) {
                if (!equal(lines[j].b, lines[l].b)) {
                    cal(l, j);
                    l = j;
                }
            }
            cal(l, i);
            if (group.size() > 1) {
                int sum = group[0].size();
                for (int v : group[0]) ++len[v];
                for (int i = 1; i < group.size(); ++i) {
                    ans += group[i].size() * sum;
                    for (int v : group[i]) sub += len[v];
                    for (int v : group[i]) ++len[v];
                    sum += group[i].size();
                }
            }
            p = i;
        }
        return ans - sub / 2;
    }
};