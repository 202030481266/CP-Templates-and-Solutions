#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

typedef unsigned long long ull;
const ull B = 233;

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
    int equalDigitFrequency(string s) {
        int n = s.size(), cnt[10][n+1];
        memset(cnt, 0, sizeof(cnt));
        vector<ull> h(n+1), power(n+1);
        for (int i = 1; i <= n; ++i) power[i] = quick_power(B, i);
        for (int i = 1; i <= n; ++i) h[i] = h[i - 1] * B + (ull)(s[i - 1]-'0'+1); // should not be zero!
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 10; ++j) {
                cnt[j][i+1] = cnt[j][i] + (s[i]-'a'==j);
            }
        }
        unordered_set<ull> vis;
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                bool ok = true;
                int N = -1;
                for (int k = 0; k < 10; ++k) {
                    if (cnt[k][j] - cnt[k][i-1] > 0) {
                        if (N == -1) N = cnt[k][j] - cnt[k][i-1];
                        else if (N != cnt[k][j] - cnt[k][i-1]) {
                            ok = false;
                            break;
                        }
                    }
                }
                if (ok) {
                    // calculate the hash
                    ull hash = h[j] - h[i-1] * power[j-i+1];
                    vis.insert(hash);
                }
            }
        }
        return vis.size();
    }
};