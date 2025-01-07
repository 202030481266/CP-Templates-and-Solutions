#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 相当有难度的题目

class Solution {
public:
    int minOperations(vector<int>& nums) {
        // 本质是求解最长的不增子序列
        vector<int> sub;
        for (int i = nums.size() - 1; i >= 0; --i) {
            int x = nums[i];
            if (sub.empty() || sub.back() <= x) {
                sub.push_back(x);
            } else {
                auto it = upper_bound(sub.begin(), sub.end(), x);
                *it = x;
            }
        }
        return sub.size();
    }
};