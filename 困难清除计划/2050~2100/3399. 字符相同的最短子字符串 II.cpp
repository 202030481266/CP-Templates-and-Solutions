#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.size(), dp[n][2];

        // check len == 1, this is hard when using greedy
        for (int i = 0; i < n; ++i) {
            int v = s[i] - '0';
            if (i==0) {
                dp[i][0]=0;
                dp[i][1]=1;
            }
            else {
                int u = s[i-1] - '0';
                if (u^v) {
                    dp[i][0] = dp[i-1][0];
                    dp[i][1] = dp[i-1][1]+1;
                }
                else {
                    dp[i][1] = dp[i-1][0]+1;
                    dp[i][0] = dp[i-1][1];
                }
            }
        }
        if (min(dp[n-1][1], dp[n-1][0]) <= numOps) return 1;

        // greedy
        int p = 0;
        vector<int> a;
        while (p < n) {
            int i = p;
            while (i < n && s[i] == s[p]) {
                i++;
            }
            a.push_back(i-p);
            p = i;
        }
        int m = a.size();
        auto check = [&](int len) -> bool {
            int c = numOps;
            for (int i = 0; i < m; ++i) {
                if (a[i] > len) {
                    int need = a[i] / (len+1);
                    if (c >= need) c -= need;
                    else return false;
                }
            }
            return true;
        };

        int l = 1, r = n+1;
        while (l + 1 < r) {
            // (l, r)
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid;
            else l = mid;
        }
        return r;
    }
};