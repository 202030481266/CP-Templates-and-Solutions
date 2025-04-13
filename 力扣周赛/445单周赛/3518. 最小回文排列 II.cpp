#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    string smallestPalindrome(string s, int k) {
        int n = s.size(), tot = 0, mid = -1;
        if (n == 1) {
            return (k == 1 ? s : "");
        }
        vector<int> cnt(26);
        for (char& ch : s) cnt[ch - 'a']++;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] & 1) mid = i;
            cnt[i] = cnt[i] / 2;
            tot += cnt[i];
        }
        string ans; 
        ans.resize(n);
        ll fac = 1, p = 25;
        int r = 1;
        while (p >= 0 && cnt[p] == 0) --p;
        for (int j = 1; r <= tot; ++r, ++j) {
            if (j > cnt[p]) {
                --p;
                while (p >= 0 && cnt[p] == 0) --p;
                j = 1;
            }
            fac = fac * r / j;
            if (fac >= k) break;
        }
        if (fac < k) return "";
        int pre = tot - r, index = 0;
        for (int i = 0; i < 26 && pre > 0; ++i) {
            if (cnt[i]) {
                int mn = min(pre, cnt[i]);
                for (int j = 0; j < mn; ++j) {
                    ans[index++] = 'a' + i;
                }
                cnt[i] -= mn;
                pre -= mn;
            }
        }
        for (; index < n / 2; ++index) {
            ll sum = 0;
            for (int j = 0; j < 26; ++j) {
                if (cnt[j]) {
                    ll c = fac * cnt[j] / r; 
                    if (sum + c >= k) {
                        fac = fac * cnt[j] / r;
                        ans[index] = 'a' + j;
                        cnt[j]--;
                        r--;
                        k -= sum;
                        break;
                    }
                    else sum += c;
                }
            }
        }
        for (int i = 0; i < n / 2; ++i) {
            ans[n - 1 - i] = ans[i];
        }
        if (mid != -1) ans[n / 2] = 'a' + mid;
        return ans;
    }
};