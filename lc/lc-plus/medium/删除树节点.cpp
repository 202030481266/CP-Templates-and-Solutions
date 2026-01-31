#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class Solution {
public:
    int deleteTreeNodes(int nodes, vector<int>& parent, vector<int>& value) {
        vector<int> g[nodes];
        int n = parent.size();
        for (int i = 1; i < n; ++i) {
            g[parent[i]].push_back(i);
        }
        function<pii(int)> dfs = [&](int u) -> pii {
            int sum = value[u], cnt = 1;
            for (int v : g[u]) {
                auto [s, c] = dfs(v);
                sum += s;
                cnt += c;
            }
            return sum != 0 ? pii(sum, cnt) : pii(0, 0);
        };
        auto [sum, cnt] = dfs(0);
        return cnt;
    }
};