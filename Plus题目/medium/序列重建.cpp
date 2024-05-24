#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class Solution {
public:
    bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences) {
        int n = nums.size();
        vector<int> cnt(n+1);
        vector<bool> vis(n+1);
        vector<int> g[n+1];
        for (auto& s : sequences) {
            vis[s[0]] = true;
            for (int i = 0; i + 1 < s.size(); ++i) {
                g[s[i]].push_back(s[i+1]);
                ++cnt[s[i+1]];
                vis[s[i]] = vis[s[i+1]] = true;
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) return false;
        }
        int cur = 0;
        for (int i = 1; i <= n; ++i) {
            if (cnt[i] == 0) {
                if (cur) return false;
                cur = i;
            }
        }
        while (cur) {
            int tmp = 0;
            for (int& v : g[cur]) {
                --cnt[v];
                if (cnt[v] == 0) {
                    if (tmp) return false;
                    tmp = v;
                }
            }
            cur = tmp;
        }
        return true;
    }
};