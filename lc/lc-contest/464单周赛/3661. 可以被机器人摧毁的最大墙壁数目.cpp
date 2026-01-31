#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = robots.size(), m = walls.size();
        ranges::sort(walls);
        vector<int> ids(n);
        vector<pii> arr;
        iota(ids.begin(), ids.end(), 0);
        ranges::sort(ids, [&](int i, int j){return robots[i] < robots[j];});
        int p = 0, ans = 0;
        for (int i : ids) {
            arr.emplace_back(robots[i], i + 1);
            while (p < m && walls[p] < robots[i]) arr.emplace_back(walls[p++], 0);
            while (p < m && robots[i] == walls[p]) ++p, ++ans;
        }
        while (p < m) arr.emplace_back(walls[p++], 0);
        ranges::sort(arr);
        n = arr.size();
        vector<int> pre(n, -1), nxt(n, n);
        p = -1;
        for (int i = 0; i < n; ++i) {
            if (arr[i].second) {
                pre[i] = p;
                p = i;
            }
        }
        p = n;
        for (int i = n - 1; i >= 0; --i) {
            if (arr[i].second) {
                nxt[i] = p;
                p = i;
            }
        }
        vector dp(n, vector<int>(2, 0));
        vector f(n, vector<int>(2, 0));
        int res = 0;
        for (int i = 0, l, r; i < n; ++i) { // 实际上最坏是O(n)的
            if (arr[i].second) {
                arr[i].second -= 1;
                l = pre[i], r = i;
                while (l + 1 < r) {
                    int mid = (l + r) >> 1;
                    if (arr[i].first - arr[mid].first <= distance[arr[i].second]) r = mid;
                    else l = mid;
                }
                f[i][0] = r;
                // [r, i)
                if (pre[i] == -1) dp[i][0] = i - r;
                else {
                    dp[i][0] = dp[pre[i]][0] + i - r;
                    if (f[pre[i]][1] >= r - 1) {
                        dp[i][0] = max(dp[i][0], dp[pre[i]][1] + i - f[pre[i]][1] - 1);
                    }
                    else {
                        dp[i][0] = max(dp[i][0], dp[pre[i]][1] + i - r);
                    }
                }
                l = i, r = nxt[i];
                while (l + 1 < r) {
                    int mid = (l + r) >> 1;
                    if (arr[mid].first - arr[i].first <= distance[arr[i].second]) l = mid;
                    else r = mid;
                }
                // (i, l]
                f[i][1] = l;
                if (pre[i] == -1) dp[i][1] = l - i;
                else dp[i][1] = max(dp[pre[i]][0], dp[pre[i]][1]) + l - i;
                res = max(res, max(dp[i][0], dp[i][1]));
            }
        }
        return res + ans;
    }
};