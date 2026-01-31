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
    typedef long long ll;
    typedef pair<int, int> pii;
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& q) {
        int cnt[n];
        map<pii, int> f;
        vector<int> g[n];
        fenwick<ll> t(100010);
        fill(cnt, cnt + n, 0);
        for (auto& e : edges) {
            int u = (--e[0]), v = (--e[1]);
            int mn = min(u, v), mx = max(u, v);
            ++cnt[u];
            ++cnt[v];
            ++f[{mn, mx}];
            if (f[{mn, mx}] == 1)
                g[mn].push_back(mx);
        }
        // 一个一个计算 q 是很不划算的，所以需要转换思路，计算贡献
        int m = q.size();
        vector<int> ans(m);
        for (int i = 0; i < n; ++i) 
            t.add(cnt[i], 1);
        for (int u = 0; u < n; ++u) {
            t.add(cnt[u], -1);
            for (int v : g[u]) {
                int tmp = cnt[v] + cnt[u] - f[{u, v}];
                for (int i = 0; i < m; ++i)
                    if (tmp > q[i]) ++ans[i];
                t.add(cnt[v], -1);
            }
            for (int i = 0; i < m; ++i) {
                if (q[i] - cnt[u] < 0) ans[i] += (n - u - 1 - g[u].size());
                else ans[i] += (n - u - 1 - g[u].size() - t.sum(q[i] - cnt[u]));
            }
            for (int v : g[u]) t.add(cnt[v], 1);
        }
        return ans;
    }
};