// https://leetcode.cn/problems/transform-array-to-all-equal-elements/description/

using ll = long long;

class Solution {
public:
    bool canMakeEqual(vector<int>& nums, int k) {
        int n = nums.size();
        // all into 1
        vector<int> a(n);
        int x = k, flag = 1;
        a[0] = nums[0];
        for (int i = 0; i + 1 < n; ++i) {
            a[i+1] = nums[i+1];
            if (a[i] < 0) {
                a[i+1] *= -1;
                if (x) --x;
                else {
                    flag = 0;
                    break;
                }
            }
        }
        if (flag && a[n-1] == 1) return true;
        a[0] = nums[0];
        x = k, flag = 1;
        for (int i = 0; i + 1 < n; ++i) {
            a[i+1] = nums[i+1];
            if (a[i] > 0) {
                a[i+1] *= -1;
                if (x) --x;
                else {
                    flag = 0;
                    break;
                }
            }
        }
        if (flag && a[n-1] == -1) return true;
        return false;
    }
};