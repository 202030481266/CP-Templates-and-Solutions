#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


class Solution {
public:
    long long minMoves(vector<int>& balance) {
        int n = balance.size();
        int p = 0;
        while (p < n && balance[p] >= 0) ++p;
        if (p == n) return 0;
        vi cnt(n);
        ll have = 0;
        for (int i = 0; i < n; ++i) {
            if (i == p) continue;
            int d1 = ((i - p) % n + n) % n;
            int d2 = ((p - i) % n + n) % n;
            cnt[min(d1, d2)] += balance[i];
            have += balance[i];
        }
        if (have + balance[p] < 0) return -1;
        ll cost = 0;
        balance[p] *= -1;
        for (int i = 1; i < n && balance[p] > 0; ++i) {
            if (balance[p] > cnt[i]) {
                cost += 1ll * i * cnt[i];
                balance[p] -= cnt[i];
            }
            else {
                cost += 1ll * i * balance[p];
                balance[p] == 0;
            }
        }
        return cost;
    }
};