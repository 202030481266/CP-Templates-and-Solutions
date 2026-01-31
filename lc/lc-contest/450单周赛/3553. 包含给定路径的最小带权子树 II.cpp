#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int maxn = 100001;
static int f[maxn][18];
static int val[maxn][18];
static int dep[maxn];

void dfs(int u, int fa, const vector<vector<pii>>& graph) {
    for (int i = 1; i < 18; ++i)
    {
        f[u][i] = f[f[u][i - 1]][i - 1];
        val[u][i] = val[u][i - 1] + val[f[u][i - 1]][i - 1];
    }
    for (auto [v, w] : graph[u])
    {
        if (v != fa)
        {
            f[v][0] = u;
            dep[v] = dep[u] + 1;
            val[v][0] = w;
            dfs(v, u, graph);
        }
    }
}

pii lca(int x, int y)
{
    if (dep[x] < dep[y]) swap(x, y);
    int cost = 0;
    for (int i = 17; i >= 0; --i)
    {
        if (dep[f[x][i]] >= dep[y]) {
            cost += val[x][i];
            x = f[x][i];
        }
    }
    if (x == y) return { x, cost };
    for (int i = 17; i >= 0; --i)
    {
	    if (f[x][i] != f[y][i])
	    {
            cost += val[x][i] + val[y][i];
            x = f[x][i];
            y = f[y][i];
	    }
    }
    cost += val[x][0] + val[y][0];
    return { f[x][0], cost };
}

class Solution {
public:
    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        vector<vector<pii>> g(n);
        for (int i = 0; i < n; ++i)
        {
            dep[i] = 0;
            for (int j = 0; j < 18; ++j) {
                f[i][j] = 0;
                val[i][j] = 0;
            }
        }
        for (auto& e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        dfs(0, -1, g);
        vector<int> ans;
        for (auto& q : queries)
        {
            ranges::sort(q, [&](const int i, const int j) { return dep[i] > dep[j]; });
            int a = q[0], b = q[1], c = q[2];
            auto [fab, fabCost] = lca(a, b);
            if (fab == b)
            {
                auto [_, fbcCost] = lca(b, c);
                ans.emplace_back(fabCost + fbcCost);
            }
            else
            {
                auto [fabc, fabcCost] = lca(fab, c);
                if (fabc == fab)
                {
                    int fac = lca(a, c).first;
                    int fbc = lca(b, c).first;
                    if (fac == c || fbc == c)
                    {
                        ans.emplace_back(fabCost);
                    }
                    else if (fac != fabc || fbc != fabc)
                    {
                        if (fac != fabc)
                        {
                            ans.emplace_back(fabCost + lca(fac, c).second);
                        }
                        else
                        {
                            ans.emplace_back(fabCost + lca(fbc, c).second);
                        }
                    }
                    else
                    {
                        ans.emplace_back(fabCost + fabcCost);
                    }
                } 
                else
                {
                    ans.emplace_back(fabCost + fabcCost);
                }
            }
        }
        return ans;
    }
};