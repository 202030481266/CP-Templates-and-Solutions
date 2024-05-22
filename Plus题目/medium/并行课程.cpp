#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<int> g[n];
        vector<int> cnt(n);
        for (auto& e : relations) {
            g[e[0] - 1].push_back(e[1] - 1);
            cnt[e[1] - 1]++;
        }
        vector<int> q;
        for (int i = 0; i < n; ++i) {
            if (cnt[i] == 0) q.push_back(i);
        }
        int ans = 0;
        for (; !q.empty();) {
            vector<int> nq;
            for (int u : q) {
                for (int v : g[u]) {
                    if (--cnt[v] == 0) nq.push_back(v);
                }
            }
            q = move(nq);
            ans++;
        }
        for (int i = 0; i < n; ++i) {
            if (cnt[i] > 0) return -1;
        }
        return ans;
    }
};
