#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

int cnt[302][26], tot[26];

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size(), m = target.size();
        for (int i = 0; i < 26; ++i) cnt[m][i] = tot[i] = 0;
        for (int i = 0; i < n; ++i) tot[s[i] - 'a']++;
        for (int i = m - 1; i >= 0; --i) {
            for (int j = 0; j < 26; ++j) cnt[i][j] = cnt[i + 1][j];
            ++cnt[i][target[i] - 'a'];
        }
        auto check = [&](auto&& self, int p) -> bool {
            if (p == m) return false;
            int x = 0, c = target[p] - 'a';
            for (int i = c + 1; i < 26; ++i) x += tot[i];
            if (x > 0) return true;
            if (tot[c] == 0) return false;
            --tot[c];
            bool res = self(self, p + 1);
            ++tot[c];
            return res;
        };
        vector<int> ans(n);
        bool big = false;
        for (int i = 0; i < min(n, m); ++i) {
            int c = target[i] - 'a';
            bool flag = 0;
            for (int j = (big ? 0 : c); j < 26; ++j) {
                if (tot[j]) { // try to emplace j
                    --tot[j];
                    bool can = big || j > c || check(check, i + 1);
                    if (can) {
                        ans[i] = j;
                        flag = 1;
                        if (j > c) big = true;
                        break;
                    }
                    else ++tot[j];
                }
            }
            if (!flag) return "";
        }
        string res;
        for (int i = 0; i < min(n, m); ++i) res.push_back((char)('a' + ans[i]));
        for (int i = 0; i < 26; ++i) {
            if (tot[i]) res.append(tot[i], (char)('a' + i));
        }
        return res;
    }
};