#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        // 枚举不同的位置就可以了，注意需要判断一个的情况
        vector<int> cnt(32);
        for (int v : nums) {
            for (int i = 0; i < 32; ++i) {
                cnt[i] += (v >> i) & 1;
            }
        }
        int ans = 0, n = nums.size();
        for (int v : nums) {
            if (v > 0) {
                ans = 1;
                break;
            }
        }
        if (ans == 0) return ans;
        for (int i = 0; i < 32; ++i) {
            int x = cnt[i], y = n - x;
            if (x & 1) ans = max(ans, n);
            else if (x > 1) ans = max(ans, y + x - 1);
        }
        return ans;
    }
};