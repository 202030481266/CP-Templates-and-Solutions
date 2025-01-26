#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

struct DSU
{
    vector<int> par, rnk, sz;
    int c;
    DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n)
    {
        for (int i = 1; i <= n; ++i)
            par[i] = i;
    }
    int find(int i)
    {
        return (par[i] == i ? i : (par[i] = find(par[i])));
    }
    bool same(int i, int j)
    {
        return find(i) == find(j);
    }
    int get_size(int i)
    {
        return sz[find(i)];
    }
    int count()
    {
        return c; // connected components
    }
    int merge(int i, int j)
    {
        if ((i = find(i)) == (j = find(j)))
            return -1;
        else
            --c;
        if (rnk[i] > rnk[j])
            swap(i, j);
        par[i] = j;
        sz[j] += sz[i];
        if (rnk[i] == rnk[j])
            rnk[j]++;
        return j;
    }
};

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<int> g[n];
        DSU dsu(n);
        for (auto& e : invocations) {
            g[e[0]].push_back(e[1]);
            dsu.merge(e[0], e[1]);
        }
        vector<int> vis(n);
        auto dfs = [&](auto&& dfs_ref, int u) -> void {
            vis[u] = 1;
            for (int v : g[u]) {
                if (!vis[v]) {
                    dfs_ref(dfs_ref, v);
                }
            }
        };
        dfs(dfs, k);
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (dsu.same(i, k) && !vis[i]) {
                ans.resize(n);
                iota(ans.begin(), ans.end(), 0);
                return ans;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (!dsu.same(i, k)) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};