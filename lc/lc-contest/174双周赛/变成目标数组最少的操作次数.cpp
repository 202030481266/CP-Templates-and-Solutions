#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vii = vector<vi>;

class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& target) {
        int n = nums.size();
        int p = 0;
        int ans = 0;
        vi ids(n);
        iota(ids.begin(), ids.end(), 0);
        ranges::sort(ids, [&](int i, int j) { return nums[i] < nums[j]; });
        while (p < n) {
            int i = p + 1;
            while (i < n && nums[ids[i]] == nums[ids[p]]) {
                ++i;
            }
            bool flag = 1;
            for (int x = p; x < i; ++x) {
                if (target[ids[x]] != nums[ids[x]]) {
                    flag = 0;
                    break;
                }
            }
            if (!flag) ++ans;
            p = i;
        }
        return ans;
    }
};
