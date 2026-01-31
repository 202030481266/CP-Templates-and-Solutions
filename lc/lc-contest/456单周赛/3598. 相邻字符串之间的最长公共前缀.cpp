#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = words.size();        
        if (n <= 2) {
            if (n == 1) return {0};
            return {0, 0};
        }
        auto cal = [&](const string& s, const string& t) {
            int i = 0;
            while (i < s.size() && i < t.size() && s[i] == t[i]) ++i;
            return i;
        };
        vector<int> ans(n);
        vector<int> pre(n);
        vector<int> suf(n);
        for (int i = 1; i < n; ++i) {
            pre[i] = max(pre[i-1], cal(words[i], words[i-1]));
        }
        for (int i = n-2; i >= 0; --i) {
            suf[i] = max(suf[i+1], cal(words[i], words[i+1]));
        }
        for (int i = 0; i < n; ++i) {
            if (i == 0) ans[i] = suf[1];
            else if (i == n - 1) ans[i] = pre[n-2];
            else {
                ans[i] = max(pre[i-1], suf[i+1]);
                ans[i] = max(ans[i], cal(words[i-1], words[i+1]));
            }
        }
        return ans;
    }
};