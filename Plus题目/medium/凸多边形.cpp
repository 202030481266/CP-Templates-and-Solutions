#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos((double) -1.0);
int sign(double x)
{
    return (x > eps) - (x < -eps);
}
struct PT
{
    double x, y;
    PT()
    {
        x = 0, y = 0;
    }
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y)    {}
    PT operator + (const PT &a) const
    {
        return PT(x + a.x, y + a.y);
    }
    PT operator - (const PT &a) const
    {
        return PT(x - a.x, y - a.y);
    }
    PT operator * (const double a) const
    {
        return PT(x * a, y * a);
    }
    friend PT operator * (const double &a, const PT &b)
    {
        return PT(a * b.x, a * b.y);
    }
    PT operator / (const double a) const
    {
        return PT(x / a, y / a);
    }
    bool operator == (PT a) const
    {
        return sign(a.x - x) == 0 && sign(a.y - y) == 0;
    }
    bool operator != (PT a) const
    {
        return !(*this == a);
    }
    bool operator < (PT a) const
    {
        return sign(a.x - x) == 0 ? y < a.y : x < a.x;
    }
    bool operator > (PT a) const
    {
        return sign(a.x - x) == 0 ? y > a.y : x > a.x;
    }
    double norm()
    {
        return sqrt(x * x + y * y);
    }
    double norm2()
    {
        return x * x + y * y;
    }
    PT perp()
    {
        return PT(-y, x);
    }
    double arg()
    {
        return atan2(y, x);
    }
    PT truncate(double r)   // returns a vector with norm r and having same direction
    {
        double k = norm();
        if (!sign(k)) return *this;
        r /= k;
        return PT(x * r, y * r);
    }
};
inline double cross(PT a, PT b)
{
    return a.x * b.y - a.y * b.x;
}
bool is_convex(vector<PT> &p)
{
    bool s[3];
    s[0] = s[1] = s[2] = 0;
    int n = p.size();
    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        int k = (j + 1) % n;
        s[sign(cross(p[j] - p[i], p[k] - p[i])) + 1] = 1;
        if (s[0] && s[2]) return 0;
    }
    return 1;
}
class Solution {
public:
    bool isConvex(vector<vector<int>>& points) {
        vector<PT> p;
        for (auto& v : points) {
            p.push_back(PT(v[0], v[1]));
        }
        return is_convex(p);
    }
};