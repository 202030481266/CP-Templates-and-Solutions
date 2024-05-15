#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumArrayLength(vector<int>& nums) {
        int n = nums.size(), cnt = 0;
        // 构造
        int mn = *min_element(nums.begin(), nums.end());
        for (int i = 0; i < n; ++i)
            if (nums[i] == mn) ++cnt;
        if (cnt == 1) return 1; // 只有一个
        for (int i = 0; i < n; ++i) {
            if (nums[i] % mn) return 1; // 可以构造一个更加小的数字
        }
        return (cnt - 1) / 2 + 1;
    }
};
