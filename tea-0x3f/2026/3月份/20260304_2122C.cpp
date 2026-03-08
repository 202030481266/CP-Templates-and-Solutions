// Problem: C. Manhattan Pairs
// Contest: Codeforces - Order Capital Round 1 (Codeforces Round 1038, Div. 1 + Div. 2)
// URL: https://codeforces.com/problemset/problem/2122/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

struct P {
    int x, y, idx;
    P() {}
};

void solve() {
    int n;
    cin >> n;
    vector<P> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].x >> arr[i].y;
        arr[i].idx = i + 1;
    }
    ranges::sort(arr, [&](const P& p1, const P& p2){
        return p1.x < p2.x;
    });
    sort(arr.begin(), arr.begin() + n / 2, [&](const P& p1, const P& p2){
        return p1.y < p2.y;
    });
    sort(arr.begin() + n / 2, arr.end(), [&](const P& p1, const P& p2){
        return p1.y < p2.y;
    });
    int l = 0, r = n - 1;
    while (l < r) {
        cout << arr[l].idx << ' ' << arr[r].idx << '\n';
        ++l;
        --r;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}