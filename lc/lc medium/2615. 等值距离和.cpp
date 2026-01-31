#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        unordered_map<int, vector<ll>> mp;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            mp[nums[i]].push_back(i);
        }
        vector<ll> ans(n);
        for (auto [key, pos] : mp) {
            int m = pos.size();
            vector<ll> sum(m+1);
            for (int i = 0; i < m; ++i) sum[i+1] = sum[i] + pos[i];
            for (int i = 0; i < m; ++i) {
                // [0, i), and (i, m-1]
                ans[pos[i]] = (pos[i] * i - sum[i]) + (sum[m]-sum[i+1] - pos[i] * (m-1-i)); 
            }
        }
        return ans;
    }
};