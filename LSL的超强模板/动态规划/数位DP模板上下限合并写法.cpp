#include <bits/stdc++.h>
using namespace std;

// https://leetcode.cn/problems/count-of-integers/

// 没有前导零的影响的模板
class Solution {
public:
    static constexpr int MOD = 1e9 + 7;
    int count(string num1, string num2, int min_sum, int max_sum) {
        int n = num2.length();
        int diffLH = n - num1.length();
        vector dp(n, vector<int>(210, -1)); //23*9=207
        if (min_sum > 207) return 0;
        max_sum = min(max_sum, 207);
        
        // 前导零不会影响最后的数字的和
        function<int(int,int,bool,bool)> dfs = [&](int p, int sum, bool limitLow, bool limitHigh)-> int {
            if (p == n) return sum >= min_sum && sum <= max_sum;
            if (!limitLow && !limitHigh) {
                if (dp[p][sum] != -1) return dp[p][sum];
                int& res = dp[p][sum];
                res = 0;
                int lo = limitLow && p >= diffLH ? num1[p-diffLH] - '0' : 0;
                int hi = limitHigh ? num2[p] - '0' : 9;
                for (int i = lo; i <= hi; i++) {
                    res += dfs(p+1, sum+i, limitLow && i == lo, limitHigh && i == hi);
                    res %= MOD;
                }
                return res;
            }
            int lo = 0;
            if (limitLow && p >= diffLH) lo = num1[p-diffLH] - '0';
            int hi = limitHigh ? num2[p] - '0' : 9;
            int res = 0;
            for (int i = lo; i <= hi; i++) {
                res += dfs(p+1, sum+i, limitLow && i == lo, limitHigh && i == hi);
                res %= MOD;
            }
            return res;
        };

        return dfs(0, 0, true, true);
    }
};

// 前导零具有影响的模板
/*
auto dfs = [&](int p, int mask, bool limitLow, bool limitHigh) -> int {
    if (p == n) {
        if (mask > 0) return 0;
        return 1;
    }
    if (!limitLow && !limitHigh) {
        int &dv = memo[p][mask];
        if (dv >= 0) return dv;
        int res = 0;
        int lo = limitLow && p >= diffLH ? lowS[p - diffLH] - '0' : 0;
        int hi = limitHigh ? highS[p] - '0' : 9;

        int d = lo;
        if (limitLow && p < diffLH) {
            res = dfs(p + 1, mask, true, false);
            ++d;
        }
        for (; d <= hi; ++d) {
            res += dfs(p + 1, mask ^ (1 << d), limitLow && d == lo, limitHigh && d == hi);
            res %= mod;
        }
        return dv = res;
    }
    int lo = 0;
    if (limitLow && p >= diffLH) lo = lowS[p - diffLH] - '0';
    int hi = limitHigh ? highS[p] - '0' : 9;

    int res = 0;
    int d = lo;
    if (limitLow && p < diffLH) {
        res = dfs(p + 1, mask, true, false);
        ++d;
    }
    for (; d <= hi; ++d) {
        res += dfs(p + 1, mask ^ (1 << d), limitLow && d == lo, limitHigh && d == hi);
        res %= mod;
    }
    return res;
};
*/