#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int i, int j) {
            return intervals[i] < intervals[j];
        });
        vector<int> right(n);
        for (int i = 0; i < n; ++i) {
            int l = -1, r = n;
            while (l + 1 < r) {
                int mid = (l + r) >> 1; 
                if (intervals[ids[mid]][0] > intervals[ids[i]][1]) r = mid;
                else l = mid;
            }
            right[i] = r;
        }

        vector dp(n+1, vector<ll>(5, -infll));
        vector mx(n+1, vector<int>(5, -1));
        vector pre(n, vector<int>(5, n));
        // init status
        dp[n][0] = 0;
        mx[n][0] = n;
        for (int i = n-1; i >= 0; --i) {
            int r = right[i];
            dp[i][0] = 0;
            mx[i][0] = i;
            if (mx[i+1][0] != -1 && mx[i+1][0] < n && ids[mx[i+1][0]] < ids[i])
                mx[i][0] = mx[i+1][0];
            for (int j = 1; j < 5; ++j) {
                int mxr = mx[r][j-1];
                if (mxr != -1) {
                    dp[i][j] = dp[mxr][j-1] + intervals[ids[i]][2];
                    pre[i][j] = mxr;
                }
                mx[i][j] = mx[i+1][j];
                if (mx[i][j] == -1 || (dp[i][j] > -infll && dp[i][j] > dp[mx[i][j]][j]) || (
                    dp[i][j] == dp[mx[i][j]][j] && ids[i] < ids[mx[i][j]]
                ))
                    mx[i][j] = i;
            }
        }
        vector<vector<int>> arr;
        ll mx_val = 0;
        for (int i = 0; i < 5; ++i) {
            mx_val = max(mx_val, dp[mx[0][i]][i]);
        }
        for (int i = 0; i < 5; ++i) {
            if (mx_val == dp[mx[0][i]][i]) {
                int cur = mx[0][i], t = i;
                vector<int> a;
                while (t) {
                    a.push_back(ids[cur]);
                    cur = pre[cur][t];
                    --t;
                }
                sort(a.begin(), a.end());
                arr.push_back(a);
            }
        }
        // cout << mx_val << endl;
        sort(arr.begin(), arr.end());
        return arr[0];
    }
};