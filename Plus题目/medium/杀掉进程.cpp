#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        unordered_map<int, vector<int>> mp;
        int n = pid.size();
        for (int i = 0; i < n; ++i) {
            mp[ppid[i]].push_back(pid[i]);
        }
        vector<int> ans;
        queue<int> q;
        q.push(kill);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ans.push_back(u);
            for (int v : mp[u]) {
                q.push(v);
            }
        }
        return ans;
    }
};