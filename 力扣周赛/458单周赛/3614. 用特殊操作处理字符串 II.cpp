#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    char processStr(string s, long long k) {
        ll n = 0;
        for (char c : s) {
            if (c == '*') {
                if (n > 0) --n;
            }
            else if (c == '#') n *= 2;
            else if (c == '%') continue;
            else {
                ++n;
            }
        }
        int m = s.size();
        for (int i = m - 1; i >= 0 && n; --i) {
            if (k >= n) return '.';
            if (s[i] == '#') {
                if (k >= n / 2) k -= n / 2;
                n /= 2;
            }
            else if (s[i] == '*') {
                ++n;
            }
            else if (s[i] == '%') {
                k = n - 1 - k;
            }
            else {
                if (k == n - 1) return s[i];
                --n;
            }
        }
        return '.';
    }
};