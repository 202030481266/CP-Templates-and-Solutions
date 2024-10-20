#include <bits/stdc++.h>
using namespace std;
// 
// using ll = long long;
// using ull = unsigned long long;
// using pii = pair<int, int>;
// const int inf = 0x3f3f3f3f;
// const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'
#define int long long

int floor_div(int a, int b) { // 向下取整
    int q = a / b;
    int r = a % b;
    if (r != 0 && ((a ^ b) < 0)) {
        q -= 1;
    }
    return q;
}

int ceil_div(int a, int b) { // 向上取整
    int q = a / b;
    int r = a % b;
    if (r != 0 && ((a ^ b) > 0)) {
        q += 1;
    }
    return q;
}

int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, a, b, c;
    cin >> n;
    while (n--) {
        cin >> a >> b >> c;
        int x, y;
        int g = extendedGCD(a, b, x, y); // ax + by = gcd(a,b)
        if (c % g != 0) {
            cout << -1 << endl;
            continue;
        }
        // ax + by = c
        x = x * (c / g);
        y = y * (c / g);
        // x = x0 + (b/g)t, y = y0 - (a/g)t
        int k = b/g, r = a/g;
        // x = x0 + kt, y = y0 - rt

        // x > 0 and y > 0
        int t0 = ceil_div(-x, k);
        if ((-x) % k == 0) t0++;
        int t1 = floor_div(y, r);
        if (y % r == 0) t1--;
        // [t1, t0]
        // a, b > 0, so k, r > 0
        if (t1 >= t0) {
            cout << t1 - t0 + 1 << ' ' << x + t0 * k << ' ' << y - t1 * r << ' ' << x + t1 * k << ' ' << y - t0 * r << endl;
        }
        else {
            cout << x + t0 * k << ' ' << y - t1 * r << endl;
        }
    }

    return 0;
}