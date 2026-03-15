#include <bits/stdc++.h>
using namespace std;



class Solution {
public:
    int longestArithmetic(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n);
        for (int i = 0; i < n; ++i) {
            if (i < 2) pre[i] = i + 1;
            else {
                if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) pre[i] = pre[i - 1] + 1;
                else pre[i] = 2;
            }
        }
        vector<int> suf(n);
        for (int i = n - 1; i >= 0; --i) {
            if (i > n - 3) suf[i] = n - i;
            else {
                if (nums[i] - nums[i + 1] == nums[i + 1] - nums[i + 2]) suf[i] = suf[i + 1] + 1;
                else suf[i] = 2;
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, max(pre[i], suf[i]));
            if (i > 0) ans = max(ans, pre[i - 1] + 1);
            if (i + 1 < n) ans = max(ans, suf[i + 1] + 1);
            if (i > 0 && i + 1 < n) {
                // ..., i-1, i, i+1, ...
                if ((nums[i - 1] + nums[i + 1]) % 2 == 0) {
                    int d = (nums[i + 1] - nums[i - 1]) / 2;
                    int left = i >= 2 && nums[i - 1] - nums[i - 2] == d ? pre[i - 1] : 1;
                    int right = i + 2 < n && nums[i + 2] - nums[i + 1] == d ? suf[i + 1] : 1;
                    ans = max(ans, left + right + 1);
                }
            }
        }
        return ans;
    }
};
