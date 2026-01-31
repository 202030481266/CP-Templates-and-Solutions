#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ull = unsigned long long;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int p = 233;

class Solution {
public:
    ull quick_power(ull a, ull b) {
        ull res = 1;
        for (; b; b >>= 1) {
            if (b & 1) res = res * a;
            a = a * a;
        }
        return res;
    }
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int n = s.size();
        vector<ull> h(n + 1);
        for (int i = 0; i < n; ++i) {
            h[i + 1] = h[i] * p + (ull)s[i];
        }
        vector<int> cnt(26);
        unordered_map<ull, int> mp;
        int ans = 0;
        for (int len = minSize; len <= maxSize; ++len) {
            int l = 1, t = 0;
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 1; i <= n; ++i) {
                ++cnt[s[i - 1] - 'a'];
                if (cnt[s[i - 1] - 'a'] == 1) {
                    ++t;
                }
                if (i - l + 1 > len) {
                    cnt[s[l - 1] - 'a']--;
                    if (cnt[s[l - 1] - 'a'] == 0) {
                        --t;
                    }
                    ++l;
                }
                if (i - l + 1 == len && t <= maxLetters) {
                    ull hash = h[i] - h[i - len] * quick_power(233, len);
                    mp[hash]++;
                    if (mp[hash] > ans) ans = mp[hash];
                }
            }
        }
        return ans;
    }
};