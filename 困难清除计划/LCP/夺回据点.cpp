class UnionFind {
public:
    vector<int> parent, size;
    vector<long long> mn; // 注意要使用long long类型不然会爆掉
    int n, setCount;
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1), mn(_n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        mn[x] = min(mn[x], mn[y]);
        --setCount;
        return true;
    }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
class Solution {
public:
    long long minimumCost(vector<int>& cost, vector<vector<int>>& roads) {
        // 思路很简单： 将图划分为多个强连通子图，缩点，然后取连通子图里面的最小值即可
        int n = cost.size();
        vector<int> vis(n), dfn(n), low(n), flag(n);

        vector<int> g[n];
        for (auto& e : roads) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        // tarjan算法求解出割点
        int tot = 0;
        function<void(int,int)> tarjan = [&](int u, int father) {
            vis[u] = 1;
            low[u] = dfn[u] = ++tot;
            int child = 0;
            for (int& v : g[u]) {
                if (!vis[v]) {
                    ++child;
                    tarjan(v, u);
                    low[u] = min(low[u], low[v]);
                    if (father != u && low[v] >= dfn[u] && !flag[u]) flag[u] = 1;
                }
                else if (v != father) low[u] = min(low[u], dfn[v]);
            }
            if (father == u && child >= 2 && !flag[u]) flag[u] = 1;
        };

        // 求解割点
        tarjan(0, 0);

        // 合并
        UnionFind un(n);
        for (int i = 0; i < n; ++i) un.mn[i] = cost[i];
        for (auto& e : roads) {
            int x = e[0], y = e[1];
            if (!flag[x] && !flag[y]) {
                un.unite(x, y);
            }
        }
        vector<int> cnt(n);
        set<int> tmp;
        for (int i = 0; i < n; ++i) {
            // O(E)
            if (flag[i]) {
                tmp.clear();
                for (int& v : g[i]) 
                    if (!flag[v])
                        tmp.insert(un.find(v));
                for (int f : tmp) ++cnt[f];
            }
        }
        long long ans = 0, mx = 0;
        for (int i = 0; i < n; ++i) {
            if (cnt[i] == 1) {
                // 可以证明只需要消除外边的 k - 1个无割点的连通块即可
                // 使用topu sort证明即可，消除之后剩下的就是割点块形成的环，那么从任何一个块出发都可以完美走完所有的点
                // 最外边的块的特征为 ： 有且只有一个割点连接
                ans += un.mn[i];
                mx = max(mx, un.mn[i]);
            }
        }
        return (ans == 0 ? *min_element(cost.begin(), cost.end()) : ans - mx); // 特判没有割点的图
    }
};