#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 100005;

ll a[maxn], c[maxn];

class Solution {
public:
    long long numOfSubsequences(string s) {
        int n = s.size();
        for (int i = 0; i <= n + 1; ++i) a[i] = c[i] = 0;
        ll ans = 0;
        for (int i = 1; i <= n; ++i) {
            a[i] = a[i-1] + (s[i - 1] == 'L');
        }
        for (int i = n; i >= 1; --i) {
            c[i] = c[i + 1] + (s[i - 1] == 'T');
        }
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] == 'C') {
                ans += a[i] * c[i];
            }
            res = max(res, a[i] * c[i]);
        }
        ll suf = 0, pre = 0;
        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] == 'C') {
                suf += c[i]; // CT
            }
        }
        for (int i = n; i >= 1; --i) {
            if (s[i - 1] == 'C') {
                pre += a[i]; // LC
            }
        }
        return ans + max(res, max(suf, pre));
    }
};