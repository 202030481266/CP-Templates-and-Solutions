#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int s = 0, n = nums.size(), all_zero = 1;
        for (int v : nums) {
            s ^= v;
            if (v) all_zero = 0;
        }
        if (all_zero) return 0;
        return s > 0 ? n : n - 1;
    }
};