#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

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
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        DSU dsu(n);
        int ans = inf;
        vector<int> arr;
        for (int i = 0; i < edges.size(); ++i) {
            auto& e = edges[i];
            if (e[3]) {
                if (dsu.same(e[0], e[1])) return -1;
                dsu.merge(e[0], e[1]);
                ans = min(ans, e[2]);
            }
            else {
                arr.push_back(i);
            }
        }
        sort(arr.begin(), arr.end(), [&](int i, int j) {
            return edges[i][2] > edges[j][2];
        });
        vector<int> val;
        for (int& i : arr) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            if (!dsu.same(u, v)) {
                dsu.merge(u, v);
                val.push_back(w);
            }
        }
        for (int i = val.size() - 1; i >= 0 && k; --i, --k) {
            val[i] *= 2;
        }
        for (int i = 0; i < n; ++i) {
            if (!dsu.same(0, i)) return -1;
        }
        for (int v : val) ans = min(ans, v);
        return ans;
    }
};