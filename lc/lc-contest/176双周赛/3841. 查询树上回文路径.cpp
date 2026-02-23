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

const int N = 1e5 + 9, LG = 18, inf = 1e9 + 9;

vector<int> g[N];
int par[N][LG + 1], dep[N], sz[N], st[N], en[N], T;
int sum[N][26];

void dfs(int u, int p = 0)
{
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    sz[u] = 1;
    st[u] = ++T;
    for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
    for (int i = 0; i < 26; ++i) sum[u][i] = sum[u][i] ^ sum[p][i];
    if (p) g[u].erase(find(g[u].begin(), g[u].end(), p));
    for (auto &v : g[u]) if (v != p)
        {
            dfs(v, u);
            sz[u] += sz[v];
            if(sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    en[u] = T;
}
int lca(int u, int v)
{
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
    if (u == v) return u;
    for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
    return par[u][0];
}

std::vector<std::string> split(const std::string& s) {
    std::istringstream iss(s);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int fenwick[26][MAXN], fn;

int lowbit(int i) {
    return i & -i;
}

void add(int idx, int p, int val) {
    while (p <= fn) {
        fenwick[idx][p] += val;
        p += lowbit(p);
    }
}

int query(int idx, int p) {
    int res = 0;
    while (p) {
        res += fenwick[idx][p];
        p -= lowbit(p);
    }
    return res;
}

int get(int idx, int u) {
    int c = query(idx, st[u]);
    c &= 1;
    return sum[u][idx] ^ c;
}
class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        for (int i = 1; i <= n; ++i) g[i].clear();
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= LG; ++j) par[i][j] = 0;
            for (int j = 0; j < 26; ++j) sum[i][j] = 0;
            dep[i] = sz[i] = st[i] = en[i] = 0;
        }
        T = 0;
        fn = n;
        for (int i = 0; i < 26; ++i) memset(fenwick[i], 0, (fn + 2) * sizeof(int));
        vector<int> val(n + 1);
        for (int i = 0; i < n; ++i) {
            val[i + 1] = s[i] - 'a';
            sum[i + 1][val[i + 1]]++;
        }
        for (auto e : edges) {
            int u = e[0] + 1, v = e[1] + 1;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1);
        vector<bool> ans;
        for (const string& q : queries) {
            auto qs = split(q);
            if (qs[0] == "query") {
                int u = stoi(qs[1]) + 1, v = stoi(qs[2]) + 1;
                int f = lca(u, v), ff = par[f][0];
                int odd = 0;
                for (int i = 0; i < 26; ++i) {
                    int cu = get(i, u), cv = get(i, v), cf = get(i, f), cff = get(i, ff);
                    if (cu ^ cv ^ cf ^ cff) {
                        ++odd;
                    }
                    if (odd > 1) break;
                }
                if (odd <= 1) ans.push_back(true);
                else ans.push_back(false);
            }
            else {
                int u = stoi(qs[1]) + 1, c = qs[2][0] - 'a';
                // [st[u], en[u]] add 1
                add(val[u], st[u], 1);
                add(val[u], en[u] + 1, -1);
                val[u] = c;
                add(val[u], st[u], 1);
                add(val[u], en[u] + 1, -1);
            }
        }
        return ans;
    }
};