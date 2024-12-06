#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        priority_queue<pii, vector<pii>, greater<pii>> q;
        vector<int> ids(n);
        iota(ids.begin(), ids.end(),0);
        sort(ids.begin(), ids.end(), [&](int i, int j){
            return tasks[i] == tasks[j] ? i < j : tasks[i] < tasks[j];  // 按照启动时间排序，然后按照时间，最后按照下标
        });
        vector<int> ans;
        int i = 0;
        ll cur = 0;
        while (!q.empty() || i < n) {
            if (q.empty()) {
                q.emplace(tasks[ids[i]][1], ids[i]);
                cur = tasks[ids[i]][0]; // 启动的时间
                i++;
            }
            else {
                auto [time, idx] = q.top();
                q.pop();
                cur += time;
                ans.push_back(idx);
                while (i < n && tasks[ids[i]][0] <= cur) {
                    q.emplace(tasks[ids[i]][1], ids[i]);
                    i++;
                }
            }
        }
        return ans;
    }
};