#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

bool validate(int x, int y) {
    if (y >= x) return false;
    int z = x ^ y;
    if (z > x) return x + y > z;
    return y + z > x;
}

void solve() {
    int x;
    cin >> x;
    if ((x & (x - 1)) == 0) {
        cout << -1 << '\n';
        return;
    }
    if ((x & (x + 1)) == 0) {
        cout << -1 << '\n';
        return;
    }
    int c = 1, y = 0;
    for (int i = 30; i >= 0; --i) {
        if ((x >> i) & 1) {
            if (c) c = 0;
        }
        else {
            if (c == 0) {
                y |= (1 << i);
                break;
            }
        }
    }
    y += (x & -x);
    
    // if (!validate(x, y)) {
    //     cout << "failed!" << '\n';
    // }
    // else {
    //     cout << "passed!" << '\n';
    // }
    cout << y << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}