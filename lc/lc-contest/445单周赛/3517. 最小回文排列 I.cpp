#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    string smallestPalindrome(string s) {
        int n = s.size(), mid = -1;
        vector<int> cnt(26, 0);
        for (int i = 0; i < n; ++i) {
            cnt[s[i]-'a']++;
        }
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] & 1) mid = i;
            cnt[i] /= 2;
        }
        string ans;
        ans.resize(n);
        for (int i = 0, j = 0; i < n/2; ++i) {
            while (j < 26 && cnt[j] == 0) j++;
            ans[i] = 'a' + j;
            cnt[j]--;
        }
        if (mid != -1) ans[n/2] = 'a' + mid;
        for (int i = n/2; i < n; ++i) {
            ans[i] = ans[n - 1 - i];
        }
        return ans;
    }
};