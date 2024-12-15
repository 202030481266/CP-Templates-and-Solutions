#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int dp[30][2];

class Solution {
public:
    int makeStringGood(string s) {
        int n = s.size();
        vector<int> cnt(30);
        for (char c : s) ++cnt[c-'a'+1];
        int mx = 0, ans = inf;
        for (int i = 1; i <= 26; ++i) {
            mx = max(mx, cnt[i]);
        }
        for (int i = 0; i <= mx; ++i) {
            memset(dp, 0x3f, sizeof(dp));
            dp[0][0] = 0;
            for (int j = 1; j <= 26; ++j) {
                if (cnt[j] == 0) {
                    dp[j][0] = min(dp[j-1][1], dp[j-1][0]); // 不能保留
                    continue;
                }
                // 保留
                if (cnt[j] < i) {
                    dp[j][1] = min(dp[j-1][1], dp[j-1][0]) + i-cnt[j]; // 朴素策略
                    // 推策略,相当j-1移除掉rem个字符转移到了s上
                    if (cnt[j-1] > i) {
                        int rem = min(cnt[j-1]-i, i-cnt[j]);
                        dp[j][1] = min(dp[j][1], dp[j-1][1]+(i-cnt[j]-rem)); 
                    }
                    if (cnt[j-1]) {
                        int rem = min(cnt[j-1], i-cnt[j]);
                        dp[j][1] = min(dp[j][1], dp[j-1][0]+(i-cnt[j]-rem));
                    }
                }
                else if (cnt[j] > i) {
                    dp[j][1] = min(dp[j-1][1], dp[j-1][0]) + cnt[j]-i;
                }
                else {
                    dp[j][1] = min(dp[j-1][1], dp[j-1][0]);
                }
                // 不保留
                dp[j][0] = min(dp[j-1][1], dp[j-1][0]) + cnt[j];
            }
            ans = min(ans, min(dp[26][0], dp[26][1]));
        }
        return ans;
    }
};