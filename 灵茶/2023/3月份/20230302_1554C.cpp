#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;


void solve() {
    int n, m;
    cin >> n >> m;
    if (n > m) {
        cout << 0 << '\n';
        return;
    }
    int w = bit_width(1u * m);
    // find minimal x satisfy such that n ^ x > m
    int x = 0, y = 1 << w;
    for (int i = w - 1; i >= 0; --i) {
        if ((m >> i) & 1) {
            if (!(n >> i & 1)) {
                x ^= 1 << i;
            }
        }
        else {
            if (n >> i & 1) {
                cout << x << '\n';
                return;
            }
            else {
                y = min(y, x ^ 1 << i);
            }
        }
    }
    cout << y << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
