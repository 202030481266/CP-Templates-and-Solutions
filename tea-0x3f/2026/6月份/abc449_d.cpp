#include <bits/stdc++.h>
using namespace std;


long long f(long long x, long long y) {
    if (x < 0 || y < 0) return 0;
    if (y > x) swap(x, y);
    long long k = y / 2 + 1;
    return k * k * 2 - k + (x / 2 - y / 2) * (y + 1);
}

long long calc(long long x1, long long y1, long long x2, long long y2) {
    if (x2 < 0) { swap(x1, x2); x1 = -x1; x2 = -x2; }
    if (y2 < 0) { swap(y1, y2); y1 = -y1; y2 = -y2; }
    if (x1 < 0) return calc(1, y1, -x1, y2) + calc(0, y1, x2, y2);
    if (y1 < 0) return calc(x1, 1, x2, -y1) + calc(x1, 0, x2, y2);
    return f(x2, y2) - f(x1-1, y2) - f(x2, y1-1) + f(x1-1, y1-1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long l, r, d, u;
    cin >> l >> r >> d >> u;
    cout << calc(l, d, r, u) << "\n";
    return 0;
}