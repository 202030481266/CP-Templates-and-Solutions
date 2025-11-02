#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        vector<int> cnt(26);
        for (char c : s) cnt[c - 'a']++;
        int n = 0, odd = 0;
        char ch;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] & 1) {
                ++odd;
                ch = i + 'a';
            }
            cnt[i] /= 2;
            n += cnt[i];
        }
        if (odd > 1) return "";
        int flag = (int)s.size() & 1;
        string ans, cur;
        auto dfs = [&](auto&& self, int p, bool is_limit) -> bool {
            if (p == n) {
                int m = cur.size();
                if (is_limit) {
                    int res = false;
                    if (flag) {
                        if (ch < target[n]) return false;
                        if (ch > target[n]) res = true;
                    }
                    if (!res) {
                        for (int i = flag ? n + 1 : n, j = m - 1; i < target.size(); ++i, --j) {
                            if (cur[j] > target[i]) {
                                res = true;
                                break;
                            }
                            if (cur[j] < target[i]) {
                                res = false;
                                break;
                            }
                        }
                    }
                    if (!res) return false;
                }
                ans = cur;
                if (flag) ans.push_back(ch);
                for (int i = m - 1; i >= 0; --i) ans.push_back(ans[i]);
                return true;
            }
            for (int i = is_limit ? target[p] - 'a' : 0; i < 26; ++i) {
                if (cnt[i]) {
                    --cnt[i];
                    cur.push_back('a' + i);
                    if (self(self, p + 1, is_limit && i == target[p] - 'a')) return true;
                    ++cnt[i];
                    cur.pop_back();
                }
            }
            return false;
        };
        if (dfs(dfs, 0, true)) return ans;
        return "";
    }
};