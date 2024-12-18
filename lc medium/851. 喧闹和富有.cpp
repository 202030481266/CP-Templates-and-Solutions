#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        vector<vector<int>> g(n);
        vector<int> ans(n);
        iota(ans.begin(), ans.end(), 0);
        vector<int> cnt(n);
        for (auto& e : richer) {
            g[e[0]].push_back(e[1]);
            ++cnt[e[1]];
        }
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (cnt[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (quiet[ans[v]] > quiet[ans[u]]) {
                    ans[v] = ans[u];
                }
                if (--cnt[v] == 0) {
                    q.push(v);
                }
            }
        }
        return ans;
    }
};