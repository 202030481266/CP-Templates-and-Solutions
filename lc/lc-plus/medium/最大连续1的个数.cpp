#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size();
        // 无限流的做法难度更高，但是属于状态机dp，更加有趣
        int pre = nums[0], a = 0, b = 0, c = 0;
        if (nums[0] == 0) a = 1;
        else b = c = 1;
        int ans = max(a,max(b,c));
        for (int i = 1; i < n; ++i) {
            int na = 0, nb = 0, nc = 0;
            if (nums[i]) {
                na = 0;
                nb = (pre == 0 ? 1 : b + 1);
                nc = (pre == 0 ? a + 1 : c + 1);
            }
            else {
                na = (pre == 0 ? 1 : b + 1);
                nb = nc = 0;
            }
            a = na, b = nb, c = nc;
            ans = max(max(ans,a), max(b,c));
            pre = nums[i];
        }
        return ans;
    }
};