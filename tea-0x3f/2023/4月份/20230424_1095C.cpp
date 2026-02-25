// Problem: C. Powers Of Two
// Contest: Codeforces - Codeforces Round 529 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1095/C
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

void solve() {
    int n, k;
    cin >> n >> k;
    int b = bit_width(1u * n), c = popcount(1u * n);
    if (c > k || k > n) {
        cout << "NO" << '\n';
        return;
    }
    vi arr(30);
    int sum = 0;
    for (int i = b - 1; i >= 0; --i) {
        if (n >> i & 1) ++arr[i], ++sum;
    }
    for (int i = b - 1; i > 0; --i) {
        while (sum < k && arr[i]) {
            --arr[i];
            ++sum;
            arr[i - 1] += 2;
        }
    }
    cout << "YES\n";
    for (int i = 0; i < b; ++i) {
        if (arr[i]) {
            while (arr[i]--) cout << (1 << i) << ' ';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}