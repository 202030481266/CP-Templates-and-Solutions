#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

ll s1[100003], s2[100003], s3[100003], pw[100003], inv[100003];

int init = [] {
    pw[0] = 1;
    inv[0] = 1;
    ll inv_10 = 700'000'005;
    for (int i = 1; i <= 100000; ++i) {
        pw[i] = pw[i - 1] * 10 % mod;
        inv[i] = inv[i - 1] * inv_10 % mod;
    }
    return 0;
}();

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            s1[i + 1] = s1[i] + (s[i] - '0');
        }
        s2[n + 1] = 0;
        s3[n + 1] = 0;
        for (int i = n; i >= 1; --i) {
            s2[i] = s2[i + 1];
            s3[i] = s3[i + 1];
            if (s[i - 1] > '0') {
                s2[i] = (s2[i] + (s[i - 1] - '0') * pw[s3[i]] % mod) % mod;
                ++s3[i];
            }
        }
        vector<int> ans;
        for (auto& q : queries) {
            int l = q[0] + 1, r = q[1] + 1;
            ll num = s2[l] - s2[r + 1], len = s3[r + 1], tot = s1[r] - s1[l - 1];
            ans.push_back(tot * num % mod * inv[len] % mod);
        }
        for (int& v : ans) v = (v + mod) % mod;
        return ans;
    }
};