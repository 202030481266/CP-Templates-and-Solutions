#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

// 打表
vector<ll> ans[17];
array<ll, 17> pw;

void init() {
    pw[0] = 1;
    for (int i = 1; i < 17; ++i) pw[i] = pw[i-1] * 10;
    vector<vector<int>> dp[17];
    dp[0].push_back({});
    for (int i = 1; i <= 9; ++i) {
        for (int j = 16; j >= i; --j) {
            for (auto way : dp[j - i]) {
                way.push_back(i);
                dp[j].push_back(way);
            }
        }
    }
    vector<pii> sol;
    vector<int> cur;
    array<int, 10> use;
    int sz, odd, num;
    auto dfs = [&](auto&& self, int n) -> void {
        if (n + odd == sz) {
            ll res = 0;
            for (int i = 0; i < cur.size(); ++i) {
                res += cur[i] * (pw[i] + pw[sz - 1 - i]);
            }
            if (sz & 1) res += pw[sz / 2] * num;
            ans[sz].push_back(res);
            return;
        }
        for (auto [val, cnt] : sol) {
            if (use[val] < cnt) {
                use[val]++;
                cur.push_back(val);
                self(self, n + 2);
                cur.pop_back();
                use[val]--;
            }
        }
    };
    for (int i = 1; i <= 16; ++i) {
        for (auto way : dp[i]) {
            int odd_cnt = 0;
            for (int v : way) {
                if (v & 1) ++odd_cnt;
            }
            if (odd_cnt > 1) continue;
            sol.clear();
            sz = 0;
            odd = 0;
            for (int v : way) {
                sol.emplace_back(v, v / 2);
                sz += v;
                if (v & 1) {
                    odd = 1;
                    num = v;
                }
            }
            dfs(dfs, 0);
        }
    }
    for (int i = 1; i <= 16; ++i) {
        ranges::sort(ans[i]);
        ans[i].erase(unique(ans[i].begin(), ans[i].end()), ans[i].end());
    }
}

bool is_init;

class Solution {
public:
    long long specialPalindrome(long long n) {
        if (!is_init) {
            is_init = true;
            init();
        }
        int m = 0;
        ll x = n;
        while (x) {
            ++m;
            x /= 10;
        }
        auto it = upper_bound(ans[m].begin(), ans[m].end(), n);
        if (it != ans[m].end()) return *it;
        return *ans[m + 1].begin();
    }
};
