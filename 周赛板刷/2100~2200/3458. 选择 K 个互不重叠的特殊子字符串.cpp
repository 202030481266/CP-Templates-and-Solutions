#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        int n = s.size(), dp[n+1];
        memset(dp, 0, sizeof(dp));
        vector<int> first(26, -1), last(26, -1);
        vector<int> is_last(n+1, 0);
        for (int i = n; i >= 1; --i) {
            int c = s[i-1] - 'a';
            if (last[c] == -1) {
                last[c] = i;
                is_last[i] = 1;
            }
        }
        for (int i = 1; i <= n; ++i) {
            int c = s[i-1] - 'a';
            if (first[c] == -1) {
                first[c] = i;
            }
        }
        for (int i = 1; i <= n; ++i) {
            int c = s[i-1] - 'a';
            if (is_last[i]) {
                int left = first[c];
                int j = i, flag = 1;
                while (j >= left) {
                    int k = s[j-1] - 'a';
                    if (last[k] > i) { // cannot be selected
                        flag = 0;
                        break;
                    }
                    left = min(left, first[s[j-1]-'a']);
                    --j;
                }
                if (flag) dp[i] = dp[j] + 1;
            }
            dp[i] = max(dp[i], dp[i-1]); // not select i
            if (dp[i] >= k) {
                if (i < n || k > 1) return true; // can't select all in one sentence
            }
        }
        return false;
    }
};