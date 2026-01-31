#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

ll a, b;

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> a >> b;
    // ax + by = 1
    ll x = 0, y = 0;
    ll g = extended_gcd(a, b, x, y);
    
    // x + bk
    ll k;
    if (x == 0) k = 1;
    else if (x > 0) k = (-x + 1) / b;
    else k = (x / b) + 1;

    cout << x + b * k << endl;
    return 0;
}