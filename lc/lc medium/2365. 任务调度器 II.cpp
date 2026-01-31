#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        int n = tasks.size();
        long long ans = 0;
        unordered_map<int, long long> mp;
        for (int i = 0; i < n; ++i)
        {
            ++ans;
            if (mp.contains(tasks[i]) && ans - mp[tasks[i]] <= space)
            {
                ans = mp[tasks[i]] + space + 1;
            }
            mp[tasks[i]] = ans;
        }
        return ans;
    }
};