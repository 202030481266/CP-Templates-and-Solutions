#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        unordered_map<int, int> cnt;
        for (int v : nums) cnt[v]++;
        
        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());

        vector<pii> arr; 
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            arr.emplace_back(nums[i]-k, cnt[nums[i]]);
            arr.emplace_back(nums[i], 0);
            arr.emplace_back(nums[i]+k+1, -cnt[nums[i]]);
        }
        sort(arr.begin(), arr.end());
        int cur = 0, m = arr.size(), ans = 0;
        for (int i = 0; i < m; ++i) {
            cur += arr[i].second;
            ans = max(ans, min(cur, cnt[arr[i].first] + numOperations));
        }
        return ans;
    }
};


