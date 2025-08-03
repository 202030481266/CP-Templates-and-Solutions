#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 100005;

int mn[maxn];

class Solution {
public:
    int earliestFinishTime(vector<int>& a1, vector<int>& b1, vector<int>& a2, vector<int>& b2) {
        int n = a1.size(), m = a2.size();
        int ed1 = inf, ed2 = inf;
        for (int i = 0; i < n; ++i) ed1 = min(ed1, a1[i] + b1[i]);
        for (int i = 0; i < m; ++i) ed2 = min(ed2, a2[i] + b2[i]);
        int ans = inf;
        for (int i = 0; i < m; ++i) {
            if (a2[i] <= ed1) ans = min(ans, ed1 + b2[i]);
            else ans = min(ans, a2[i] + b2[i]);
        }
        for (int i = 0; i < n; ++i) {
            if (a1[i] <= ed2) ans = min(ans, ed2 + b1[i]);
            else ans = min(ans, a1[i] + b1[i]);
        }
        return ans;
    }
};