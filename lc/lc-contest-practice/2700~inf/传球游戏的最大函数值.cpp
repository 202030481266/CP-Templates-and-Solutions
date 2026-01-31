// 基环树，先把所有的环找出来然后再进行分析
// O(n)算法
class Solution {
    int n;
    vector<vector<int>> rg;
    vector<int> in, vis;
    vector<int> receiver;
    long long ans = 0, k;
public:
    void f(int st) {
        vector<int> cycle{st};
        int cur = receiver[st];
        vis[st] = 1;
        while (cur != st) {
            vis[cur] = 1;
            cycle.push_back(cur);
            cur = receiver[cur];
        }
        int m = cycle.size();
        vector<long long> sum(2 * m + 1);
        for (int i = 0; i < 2 * m; ++i) 
            sum[i + 1] = sum[i] + cycle[i % m];
        long long time = (k / m) * sum[m]; 
        for (int i = 1; i <= m; ++i) 
            ans = max(ans, time + sum[i + k % m] - sum[i - 1]);
        for (int j = 1; j <= m; ++j) {
            int u = cycle[j - 1];
            vector<int> path;
            vector<long long> pre{0};
            for (int& v : rg[u]) {
                if (in[v] == 0) {
                    dfs(v, path, pre, sum, m, j);
                }
            }
        }
    }
    void dfs(int u, vector<int>& path, vector<long long>& pre, vector<long long>& sum, int& m, int& j) {
        path.push_back(u);
        pre.push_back(pre.back() + u);
        int ps = path.size();
        // cout << u << ' ' << path.back() << ' ' << pre.back() << endl;
        if (ps <= k)
            ans = max(ans, pre.back() + (k - ps) / m * sum[m] + sum[j + (k - ps) % m] - sum[j - 1]);
        else ans = max(ans, pre[ps] - pre[ps - k - 1]);
        for (int& v : rg[u])
            dfs(v, path, pre, sum, m, j);
        path.pop_back();
        pre.pop_back();
    }
    long long getMaxFunctionValue(vector<int>& receiver, long long K) {
        n = receiver.size(), k = K;
        rg = vector(n, vector<int>());
        in.resize(n);
        vis.resize(n);
        this->receiver = receiver;
        for (int i = 0; i < n; ++i) {
            rg[receiver[i]].push_back(i);
            ++in[receiver[i]];
        }
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (in[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            --in[receiver[u]];
            if (in[receiver[u]] == 0) q.push(receiver[u]);
        }
        for (int i = 0; i < n; ++i) {
            if (in[i] > 0 && !vis[i]) f(i);
        }
        return ans;
    }
};