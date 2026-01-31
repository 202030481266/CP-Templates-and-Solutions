#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int countWays(vector<int>& nums) {
        // 枚举选的人数即可
        int n = nums.size(), ans = 0;
        sort(nums.begin(), nums.end());
        int p = 0;
        for (int i = 0; i <= n; ++i) {
            // [0,p)
            while (p < n && nums[p] < i) ++p;
            if (p==i && (p == n || nums[p] > i)) ++ans;
        }
        return ans;
    }
};
