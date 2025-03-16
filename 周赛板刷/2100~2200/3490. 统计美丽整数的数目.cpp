#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// 和很小，乘积很大，利用和来减小乘积的空间

class Solution {
public:
    int solve(int N, int M) {
        string s = to_string(N);
        reverse(s.begin(), s.end());
        int n = s.size();
        vector dp(n, vector(M + 1, vector<int>(M + 1, -1)));
        auto cal = [&](auto&& dfs, int p, int mul, int sum, bool is_limited, bool is_num) -> int {
            if (p < 0) return (mul == 0 && is_num && sum == M);
            if (!is_limited && is_num && dp[p][sum][mul] != -1) return dp[p][sum][mul]; 
            int res = 0, up = (is_limited ? s[p] - '0' : 9);
            if (!is_num) {
                res += dfs(dfs, p - 1, 1, 0, false, false);
                for (int i = 1; i <= up && i <= M; ++i) {
                    res += dfs(dfs, p - 1, i % M, i, 
                                is_limited && (i == up), true);
                }
            }
            else {
                for (int i = 0; i <= up && sum + i <= M; ++i) {
                    res += dfs(dfs, p - 1, (mul * i) % M, sum + i, 
                                is_limited && (i == up), true);
                }
            }
            if (!is_limited && is_num) dp[p][sum][mul] = res;
            return res;
        };
        return cal(cal, n-1, 1, 0, true, false);
    }
    int beautifulNumbers(int l, int r) {
        string sl = to_string(l), sr = to_string(r);
        int mx_sum = max((int)sr.size(), (int)sl.size()) * 9, ans = 0;
        for (int s = 1; s <= mx_sum; ++s) {
            ans += solve(r, s) - solve(l - 1, s);
        }
        return ans;
    }
};