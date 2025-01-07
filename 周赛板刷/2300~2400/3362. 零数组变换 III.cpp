#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), cur = 0, m = queries.size();
        int p = 0, ans = 0;
        sort(queries.begin(), queries.end());
        multiset<pii> s;
        vector<int> sum(n+1);
        for (int i = 0; i < n; ++i) {
            while (p < m && queries[p][0] <= i) {
                s.emplace(queries[p][1], queries[p][0]);
                ++p;
            }
            while (!s.empty() && s.begin()->first < i) {
                auto it = s.begin();
                s.erase(it);
                ++ans;
            }
            cur += sum[i];
            while (!s.empty() && cur < nums[i]) {
                auto it = s.rbegin();
                int l = it->second, r = it->first;
                s.erase(prev(s.end()));
                cur++;
                sum[r+1]--;
            }
            if (cur < nums[i]) return -1;
        } 
        return ans + s.size();
    }
};