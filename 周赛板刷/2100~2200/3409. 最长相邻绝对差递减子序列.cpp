#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

template <class T>
struct fenwick {
    vector<T> t;

    fenwick(int n) : t(n) {}

    void add(int i, T value) {
        for (; i < t.size(); i |= i + 1)
            t[i] = max(t[i], value);
    }

    // sum[0..i]
    T sum(int i) {
        T res{};
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res = max(res, t[i]);
        return res;
    }
};

class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int m = *max_element(nums.begin(), nums.end());
        vector<int> arr;
        vector<int> vis(m+1);
        vector<fenwick<int>> f(m+1, fenwick<int>(m+1));
        vector<int> dp(m+1);
        int ans = 0;
        for (int i = n-1; i >= 0; --i) {
            fill(dp.begin(), dp.end(), 0);
            for (int j : arr) {
                int d = abs(nums[i] - j);
                dp[d] = max(dp[d], f[j].sum(d) + 1);
            }
            for (int j = 0; j < m; ++j) {
                if (dp[j]) {
                    ans = max(ans, dp[j]);
                    f[nums[i]].add(j, dp[j]);
                }
            }
            if (!vis[nums[i]]) {
                arr.push_back(nums[i]);
                vis[nums[i]] = 1;
            }
        }
        return ans+1;
    }
};