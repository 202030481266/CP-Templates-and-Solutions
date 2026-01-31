#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

int mx_c[100005], mn_c[100005];
int mx_r[100005], mn_r[100005];

class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        for (int i = 1; i <= n; ++i) {
            mx_c[i] = mx_r[i] = 0;
            mn_c[i] = mn_r[i] = inf;
        }
        for (auto& b : buildings) {
            int x = b[0], y = b[1];
            mx_c[y] = max(mx_c[y], x);
            mn_c[y] = min(mn_c[y], x);
            mx_r[x] = max(mx_r[x], y);
            mn_r[x] = min(mn_r[x], y);
        }
        int ans = 0;
        for (auto& b : buildings) {
            int x = b[0], y = b[1];
            if (x > mn_c[y] && x < mx_c[y] && y > mn_r[x] && y < mx_r[x]) {
                ans++;
            }
        }
        return ans;
    }
};