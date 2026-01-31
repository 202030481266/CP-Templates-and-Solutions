// logtrick 模板题目
// 更加详细的技巧讲解：https://leetcode.cn/circle/discuss/50YKkt/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int tar) {
        unordered_map<int, int> mp;
        ll ans = 0;
        for (int v : nums) {
            unordered_map<int, int> s;
            for (auto [k, val] : mp) { // 拼接之前的
                s[k & v] += val;
            }
            s[v] += 1; // 不拼接
            ans += s[tar];
            mp = move(s);
        }
        return ans;
    }
};