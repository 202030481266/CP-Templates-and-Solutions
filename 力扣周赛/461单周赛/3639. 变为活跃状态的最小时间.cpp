#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    int minTime(string str, vector<int>& order, int k) {
        int n = str.size();
        set<int> s{-1, n};
        ll tot = 1ll * n * (n + 1) / 2;
        ll cur = tot;
        for (int i = 0; i < order.size(); ++i) {
            int p = order[i];
            auto it = s.lower_bound(p);
            int len = *it - *prev(it) - 1; // (l,r)
            cur -= 1ll * len * (len + 1) / 2;
            int l = *it - p - 1, r = p - *prev(it) - 1;
            cur += 1ll * l * (l + 1) / 2;
            cur += 1ll * r * (r + 1) / 2;
            s.insert(p);
            if (tot - cur >= k) return i;
        }
        return -1;
    }
};