#include <bits/stdc++.h>
using namespace std;

// using ll = long long;
// using ull = unsigned long long;
// using pii = pair<int, int>;
// const int inf = 0x3f3f3f3f;
// const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define int long long
#define endl '\n'

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

    int x, y, n, m, L;
    cin >> x >> y >> n >> m >> L;

    int A, B;
    if (n == m) {
        if (x == y) cout << 0 << endl;
        else cout << "Impossible" << endl;
        return 0;
    }
    // x + n * time, y + m * time
    if (n > m) {
        A = n - m; 
        B = x - y;
    }
    else {
        A = m - n;
        B = y - x;
    }

    B = (-B % L + L) % L;
    A %= L;
    // Ax = B (mod L)
    int g = extendedGCD(A, L, x, y); // Ax + Ly = gcd(A, L)
    // Ax + yL = B
    if (B % g != 0) {
        cout << "Impossible" << endl;
        return 0;
    }
    // x = x0 + k * t 
    int x0 = x * (B / g), k = L / g;
    // t >= -x0 / k
    int t = ceil_div(-x0, k);

    cout << x0 + k * t << endl;

    return 0;
}