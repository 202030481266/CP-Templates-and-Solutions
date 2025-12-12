// Problem: P9474 [yLOI2022] 长安幻世绘
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9474
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// 在值域上做滑窗，维护当前的值域在数组上分布的能够取到的最大值，因为问题存在单调性，对于每一个新加入的值，必然存在一个最大的最小值


#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int n, arr[MAXN], pos[MAXN], b[MAXN];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) b[i] = i;
    sort(b + 1, b + 1 + n, [&](int i, int j){ return arr[i] < arr[j]; });
    for (int i = 1; i <= n; ++i) pos[b[i]] = i;
    int l = 1, ans = INF;
    for (int i = 1; i <= n; ++i) {
        
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}