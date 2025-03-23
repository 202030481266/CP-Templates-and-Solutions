#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// O(n * m)

class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size(), m = mana.size();
        ll start = 0;
        vector sum(2, vector<ll>(n + 1, 0));
        int pre = 0, cur = 1;
        for (int i = 0; i < n; ++i) {
            sum[pre][i + 1] = sum[pre][i] + skill[i] * mana[0];
        }
        for (int j = 1; j < m; ++j) {
            ll nxt_start = 0;
            for (int i = 0; i < n; ++i) {
                sum[cur][i + 1] = sum[cur][i] + skill[i] * mana[j];
                nxt_start = max(nxt_start, start + sum[pre][i + 1] - sum[cur][i]);
            }
            start = nxt_start;
            swap(pre, cur);
        }
        return start + sum[pre][n];
    }
};