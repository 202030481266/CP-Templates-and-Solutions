// Problem: F. Rain and Umbrellas
// Contest: Codeforces - Codeforces Round 486 (Div. 3)
// URL: https://codeforces.com/contest/988/problem/F
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
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

void solve() {
    int n, m, dst;
    cin >> n >> m >> dst;
    vector<pii> rain(n);
    vector<pii> unb(m);
    stack<pii> st;
    for (int i = 0; i < n; ++i) cin >> rain[i].first >> rain[i].second;
    for (int i = 0; i < m; ++i) cin >> unb[i].first >> unb[i].second;
    ranges::sort(rain);
    ranges::sort(unb);
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}