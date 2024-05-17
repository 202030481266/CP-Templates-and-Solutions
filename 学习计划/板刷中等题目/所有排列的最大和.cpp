#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        int n = nums.size(), a[n+1];
        memset(a, 0, sizeof(a));
        for (auto& q : requests) {
            // [l,r] -> a[l]++, a[r+1]--
            a[q[0]]++;
            a[q[1]+1]--;
        }
        vector<int> b;
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            cnt += a[i];
            if (cnt > 0) b.push_back(cnt);
        }
        sort(b.begin(), b.end());
        sort(nums.begin(), nums.end());
        long long ans = 0;
        for (int i = n - 1, j = (int)b.size() - 1; i >= 0 && j >= 0; --j, --i) {
            ans += 1ll * b[j] * nums[i];
            ans %= 1000000007;
        }
        return ans;
    }
};
