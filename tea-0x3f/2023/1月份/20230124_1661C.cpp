#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;


void solve() {
    // (n+1)/2 * 1, n/2 * 2
    int n;
    cin >> n;
    vi arr(n);
    for (int& v : arr) cin >> v;
    int mx = *max_element(arr.begin(), arr.end());
    auto f = [&](int val) -> ll {
        ll two = 0, one = 0;
        for (int v : arr) {
            int x = val - v;
            if (x & 1) ++one;
            two += x / 2;
        }
        if (two <= one) return two < one ? 2 * one - 1 : two * 2;
        ll d = (two * 2 + one) / 3, r = (two * 2 + one) % 3;
        if (r == 0) return d * 2;
        if (r == 1) return 2 * d + 1;
        return 2 * d + 2;
    };
    cout << min(f(mx), f(mx + 1)) << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
