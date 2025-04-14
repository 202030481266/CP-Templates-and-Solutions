#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

template <class T>
struct fenwick {
    vector<T> t;

    fenwick(int n) : t(n) {}

    void add(int i, T value) {
        for (; i < t.size(); i |= i + 1)
            t[i] += value;
    }

    // sum[0..i]
    T sum(int i) {
        T res{};
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res += t[i];
        return res;
    }

    // returns min(p | sum[0..p] >= sum)
    // requires non-negative tree values
    int lower_bound(T sum) {
        int highest_one_bit = 1;
        while (highest_one_bit << 1 <= t.size())
            highest_one_bit <<= 1;
        int pos = 0;
        // 使用倍增的方法来进行查找
        for (size_t blockSize = highest_one_bit; blockSize != 0; blockSize >>= 1) {
            int p = pos + blockSize - 1;
            if (p < t.size() && t[p] < sum) {
                sum -= t[p];
                pos += blockSize;
            }
        }
        return pos;
    }
};


class Solution {
public:
    vector<vector<pii>> g;
    vector<int> dis, dfn, ids, f, val, siz;
    int tot = 0;
    void dfs(int u, int fa) {
        dfn[u] = ++tot;
        ids[tot] = u;
        f[u] = fa;
        siz[u] = 1;
        for (auto [v, w] : g[u]) {
            if (v != fa) {
                dis[v] = dis[u] + w;
                val[v] = w;
                dfs(v, u);
                siz[u] += siz[v];
            }
        }
    }
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        g.resize(n+1);
        dis.resize(n+1);
        dfn.resize(n+1);
        ids.resize(n+1);
        val.resize(n+1);
        siz.resize(n+1);
        f.resize(n+1);
        tot = 0;
        for (auto& e : edges) {
            g[e[0]].emplace_back(e[1], e[2]);
            g[e[1]].emplace_back(e[0], e[2]);
        }
        dfs(1, 0);
        fenwick<int> tree(n+7);
        for (int i = 1; i <= n; ++i) {
            // dfn
            tree.add(i, dis[ids[i]]-dis[ids[i-1]]);
        }
        vector<int> ans;
        for (auto& q : queries) {
            if (q[0] == 1) {
                int u = q[1], v = q[2];
                if (f[u] == v) swap(u, v);
                int l = dfn[v], r = dfn[v] + siz[v] - 1;
                int change = q[3] - val[v]; 
                val[v] = q[3];
                // [l,r]
                tree.add(l, change);
                tree.add(r+1, -change);
            }
            else {
                int x = q[1];
                ans.push_back(tree.sum(dfn[x]));
            }
        }
        return ans;
    }
};