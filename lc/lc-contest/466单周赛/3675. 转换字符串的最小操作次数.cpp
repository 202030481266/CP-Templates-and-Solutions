#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        vector<int> cnt(26);
        for (char c : s) cnt[c - 'a'] = 1;
        int ans = 0, pre = -1;
        for (int i = 1; i < 26; ++i) {
            if (cnt[i]) {
                if (pre == -1) pre = i;
                else {
                    ans += i - pre;
                    pre = i;
                }
            }
        }
        if (pre != -1) ans += 26 - pre;
        return ans;
    }
};