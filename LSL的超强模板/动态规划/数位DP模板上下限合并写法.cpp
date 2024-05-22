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

// 使用GPT-4o翻译的cpp模板
#include <vector>
#include <string>
#include <functional>
#include <iostream>

const int mod = 1e9 + 7;

int digitDP(int low, int high, int sumUpper) {
    std::string lowS = std::to_string(low); // 不加前导零
    std::string highS = std::to_string(high);
    int n = highS.size();
    int diffLH = n - lowS.size();
    std::vector<std::vector<int>> memo(n, std::vector<int>(sumUpper + 1, -1));

    // 第一种写法（前导零不影响答案）
    std::function<int(int, int, bool, bool)> f = [&](int p, int sum, bool limitLow, bool limitHigh) -> int {
        if (p == n) {
            // 不合法
            if (sum > sumUpper) {
                return 0;
            }
            // 合法
            return 1;
        }
        if (!limitLow && !limitHigh) {
            int &dv = memo[p][sum];
            if (dv >= 0) {
                return dv;
            }
            int res = 0;
            dv = res; // 需要返回res之后再保存
        }

        int lo = 0;
        if (limitLow && p >= diffLH) {
            lo = lowS[p - diffLH] - '0';
        }
        // 注：不要修改这里！如果对数位有其它限制，应当写在下面 for 循环中
        int hi = 9;
        if (limitHigh) {
            hi = highS[p] - '0';
        }

        int res = 0;
        for (int d = lo; d <= hi; ++d) {
            res += f(p + 1, sum + d, limitLow && d == lo, limitHigh && d == hi);
            res %= mod;
        }
        if (!limitLow && !limitHigh) {
            memo[p][sum] = res;
        }
        return res;
    };
    // int ans = f(0, 0, true, true);

    // 第二种写法（前导零影响答案）
    // 注意，仍然无需使用 isNum
    // 下面是计算每个数都出现偶数次的方案数
    std::function<int(int, int, bool, bool)> dfs = [&](int p, int mask, bool limitLow, bool limitHigh) -> int {
        if (p == n) {
            // 如果 low=0，那么 0 是题目允许的吗？
            //if (limitLow) {
            //    return 0;
            //}
            if (mask > 0) {
                return 0;
            }
            return 1;
        }
        if (!limitLow && !limitHigh) {
            int &dv = memo[p][mask];
            if (dv >= 0) {
                return dv;
            }
            int res = 0;
            dv = res; // 需要返回res之后再保存
        }

        int lo = 0;
        if (limitLow && p >= diffLH) {
            lo = lowS[p - diffLH] - '0';
        }
        // 注：不要修改这里！如果对数位有其它限制，应当写在下面 for 循环中
        int hi = 9;
        if (limitHigh) {
            hi = highS[p] - '0';
        }

        int res = 0;
        int d = lo;
        if (limitLow && p < diffLH) {
            // 什么也不填
            res = dfs(p + 1, mask, true, false);
            d++;
        }
        for (; d <= hi; ++d) {
            res += dfs(p + 1, mask ^ (1 << d), limitLow && d == lo, limitHigh && d == hi);
            res %= mod;
        }
        if (!limitLow && !limitHigh) {
            memo[p][mask] = res;
        }
        return res;
    };
    int ans = dfs(0, 0, true, true);
    return ans;
}

int main() {
    int low = 1, high = 100, sumUpper = 10;
    std::cout << digitDP(low, high, sumUpper) << std::endl;
    return 0;
}
