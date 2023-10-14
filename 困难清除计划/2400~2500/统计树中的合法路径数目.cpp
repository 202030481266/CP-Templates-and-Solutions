class UnionFind {
public:
    vector<int> parent, size;
    int n, setCount;
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
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
        --setCount;
        return true;
    }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
class Solution {
    int pri[100010];
public:
    vector<int> generate_primes_linear_time(int n) {
        vector<int> lp(n + 1);
        vector<int> primes;
        for (int i = 2; i <= n; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                pri[i] = 1;
                primes.push_back(i);
            }
            for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= n; ++j)
                lp[i * primes[j]] = primes[j];
        }
        return primes;
    }
    long long countPaths(int n, vector<vector<int>>& edges) {
        // primes 确定
        auto primes = generate_primes_linear_time(n);

        // 连通块的建立和图的建立
        UnionFind un(n + 1);
        vector<int> g[n + 1];
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            if (!pri[u] && !pri[v]) un.unite(u, v);
            else {
                if (pri[u] && !pri[v]) g[u].push_back(v);
                if (!pri[u] && pri[v]) g[v].push_back(u);
            }
        }

        // 统计
        long long ans = 0;
        for (int& p : primes) {
            long long sum = 0, sub = 0;
            for (int& v : g[p]) {
                int f = un.find(v); 
                long long sz = un.size[f];
                sum += sz;
                sub += (sz) * (sz - 1) / 2;
            }
            ans += (sum + (sum * (sum - 1)) / 2 - sub);
        }
        return ans;
    }
}; 