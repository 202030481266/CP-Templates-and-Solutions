#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


class Solution {
public:
    int almostPalindromic(string s) {
        int ans = 0;
        int n = s.size();
        auto match = [&](int& l, int& r) -> void {
            while (l >= 0 && r < n && s[l] == s[r]) {
                --l;
                ++r;
            }
        };
        auto cal = [&](int l, int r) -> void {
            match(l, r);
            ans = max(ans, r - l - 1);
            int nl, nr;
            if (l >= 0) {
                nl = l - 1;
                nr = r;
                match(nl, nr);
                ans = max(ans, nr - nl - 1);
            }
            if (r < n) {
                nl = l; 
                nr = r + 1;
                match(nl, nr);
                ans = max(ans, nr - nl - 1);
            }
        };
        for (int i = 0; i < n; ++i) cal(i - 1, i + 1);
        for (int i = 0; i < n; ++i) cal(i, i + 1);
        return ans;
    }
};