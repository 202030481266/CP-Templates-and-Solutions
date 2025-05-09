// https://uoj.ac/problem/763

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

const ull mask = mt19937_64(time(nullptr))();

ull shift(ull x) {
    x ^= mask;
    x ^= (x << 13);
    x ^= (x >> 7);
    x ^= (x << 17);
    x ^= mask;
    return x;
}

const int maxn = 1e6 + 7;
ull hashValue[maxn];
vector<int> g[maxn];
set<ull> trees; // unordered_set常数略微小

void dfs(int u, int fa) {
    hashValue[u] = 1;
    for (int& v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        hashValue[u] += shift(hashValue[v]);
    }
    trees.insert(hashValue[u]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    cout << trees.size() << '\n';
}