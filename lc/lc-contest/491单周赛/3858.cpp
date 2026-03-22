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
    int minimumOR(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int ans = 0, mask = 0;
        for (int i = 17; i >= 0; --i) {
            mask |= 1 << i;
            int can = 1;
            for (auto g : grid) {
                int flag = 0;
                for (int v : g) {
                    if (mask & v) continue;
                    flag = 1;
                    break;
                }
                if (!flag) {
                    can = 0;
                    break;
                }
            }
            if (!can) {
                mask ^= 1 << i;
                ans |= 1 << i;
            }
        }
        return ans;
    }
};