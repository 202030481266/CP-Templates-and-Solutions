#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    vector<int> baseUnitConversions(vector<vector<int>>& conversions) {
        int n = conversions.size() + 1;
        vector<int> ans(n, 1);
        queue<int> q;
        q.push(0);
        vector<pii> g[n];
        for (auto& e : conversions) {
            int s = e[0], t = e[1], w = e[2];
            g[s].emplace_back(t, w);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto [v, w] : g[u]) {
                ans[v] = 1ll * ans[u] * w % mod;
                q.push(v);
            }
        }
        return ans;
    }
};