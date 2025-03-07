#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> q(n+1);
        int l = 0, r = 0;
        // 单调队列或者前后缀最小值维护都行
        q[r++] = 0;
        for (int i = 1; i < n; ++i) {
            while (l < r && nums[q[r-1]] >= nums[i]) r--;
            q[r++] = i;
        }
        int mn = 0, ans = inf;
        for (int i = 1; i < n-1; ++i) {
            while (l < r && q[l] <= i) l++;
            if (nums[mn] < nums[i] && nums[i] > nums[q[l]]) {
                ans = min(ans, nums[i] + nums[mn] + nums[q[l]]);
            }
            if (nums[i] < nums[mn]) mn = i;
        }
        return (ans == inf ? -1 : ans);
    }
};