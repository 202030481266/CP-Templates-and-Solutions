// Problem: D. Maximum AND
// Contest: Codeforces - Educational Codeforces Round 134 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1721/D
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

int node[3000005][2], tot = 0, root;
int cnt[3000005];

int alloc() {
    ++tot;
    node[tot][0] = 0;
    node[tot][1] = 0;
    cnt[tot] = 0;
    return tot;
}

void insert(int val, vector<int>& bp) {
    int u = root;
    for (int b : bp) {
        int x = val >> b & 1;
        if (!node[u][x]) node[u][x] = alloc();
        u = node[u][x];
    }
    cnt[u]++;
}

int check(int val, vector<int>& bp) {
    int u = root;
    for (int b : bp) {
        int x = val >> b & 1;
        if (!node[u][x ^ 1]) return 0;
        u = node[u][x ^ 1];
    }
    if (cnt[u] == 0) return 0;
    --cnt[u];
    return 1;
}
        
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    int mx = 0;
    for (int& v : a) {
        cin >> v;
        mx = max(mx, v);
    }
    for (int& v : b) {
        cin >> v;
        mx = max(mx, v);
    }
    int w = bit_width(1u * mx);
    vector<int> pos;
    for (int i = w - 1; i >= 0; --i) {
        pos.push_back(i);
        tot = 0;
        root = alloc();
        for (int v : a) {
            insert(v, pos);
        }
        bool flag = 1;
        for (int v : b) {
            if (!check(v, pos)) {
                flag = 0;
                break;
            }
        }
        if (!flag) pos.pop_back();
    }
    int ans = 0;
    for (int v : pos) ans |= 1 << v;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}

