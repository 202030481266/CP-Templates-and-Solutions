#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    string removeSubstring(string s, int k) {
        int n = s.size();
        vector<pair<char, int>> arr;
        int p = 0;
        while (p < n) {
            int i = p + 1;
            while (i < n && s[p] == s[i]) ++i;
            arr.emplace_back(s[p], i - p);
            p = i;
        }
        stack<pair<char, int>> stk;
        for (auto [c, v] : arr) {
            if (stk.empty()) {
                stk.emplace(c, v);
            }
            else {
                if (c == '(') {
                    if (stk.top().first == '(') {
                        int num = stk.top().second;
                        stk.pop();
                        stk.emplace(c, v + num);
                    }
                    else {
                        stk.emplace(c, v);
                    }
                }
                else {
                    if (stk.top().first == ')') {
                        int num = stk.top().second;
                        stk.pop();
                        v += num;
                    }
                    while (!stk.empty() && stk.top().first == '(' && stk.top().second >= k && v >= k) {
                        int num = stk.top().second;
                        stk.pop();
                        num -= k;
                        v -= k;
                        if (num > 0) stk.emplace('(', num);
                        if (!stk.empty() && stk.top().first == ')') {
                            num = stk.top().second;
                            v += num;
                            stk.pop();
                        }
                    }
                    if (v > 0) stk.emplace(c, v);
                }
            }
        }
        string ans;
        while (!stk.empty()) {
            ans.append(stk.top().second, stk.top().first);
            stk.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};