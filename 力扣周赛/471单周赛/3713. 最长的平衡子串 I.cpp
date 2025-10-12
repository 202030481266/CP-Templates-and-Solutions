#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

int cnt[100002][26];

class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 26; ++j) cnt[i][j] = cnt[i-1][j];
            cnt[i][s[i - 1] - 'a']++;
        }
        int ans = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                int num = cnt[j][s[i - 1] - 'a'] - cnt[i - 1][s[i - 1] - 'a'];
                int flag = 1;
                for (int k = 0; k < 26; ++k) {
                    if (cnt[j][k] - cnt[i - 1][k] > 0 && cnt[j][k] - cnt[i - 1][k] != num) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) ans = max(ans, j - i + 1);
            }
        }
        return ans;
    }
};