#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    string processStr(string s) {
        string ans;
        for (char c : s) {
            if (c == '*') {
                if (ans.size()) ans.pop_back();
            }
            else if (c == '#') {
                ans = ans + ans;
            }
            else if (c == '%') {
                reverse(ans.begin(), ans.end());
            }
            else {
                ans.push_back(c);
            }
        }
        return ans;
    }
};