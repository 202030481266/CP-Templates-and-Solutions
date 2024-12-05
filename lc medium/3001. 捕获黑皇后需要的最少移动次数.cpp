#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
        if (a == e && (c != a || d < min(b,f) || d > max(b,f))) return 1;
        if (b == f && (d != b || c < min(a,e) || c > max(a,e))) return 1;
        if (c + d == e + f && (a + b != c + d || a-b < min(c-d, e-f) || a-b > max(c-d, e-f)))
            return 1;
        if (c - d == e - f && (a - b != c - d || a+b < min(c+d, e+f) || a+b > max(c+d, e+f)))
            return 1;
        return 2;
    }
};