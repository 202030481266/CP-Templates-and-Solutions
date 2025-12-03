// Problem: D. Sea Battle
// Contest: Codeforces - Technocup 2017 - Elimination Round 2
// URL: https://codeforces.com/contest/729/problem/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

void solve() {
    int n, a, b, k;
    cin >> n >> a >> b >> k;
    vector<char> arr(n);
    vector<pii> num;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    int p = 0;
    while (p < n) {
        if (arr[p] == '1') {
            ++p;
            continue;
        }
        int i = p + 1;
        while (i < n && arr[i] == '0') ++i;
        if (i - p >= b) num.emplace_back(p, i - p);
        p = i;
    }
    n = num.size();
    vector<int> sum(n + 1);
    vector<int> pos;
    for (int i = n - 1; i >= 0; --i) sum[i] = sum[i + 1] + num[i].second / b;
    for (int i = 0; i < n; ++i) {
        int cur = num[i].second, k = 1;
        while (cur >= b && cur / b + sum[i + 1] >= a) {
            pos.push_back(num[i].first + k * b - 1);
            cur -= b;
            ++k;
        }
    }
    cout << pos.size() << '\n';
    for (int v : pos) cout << v + 1 << ' ';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}