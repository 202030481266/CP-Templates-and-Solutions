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

int a[5001];
int flag;
vii b;


class Solution {
public:
    int countArrays(vector<int>& digitSum) {
        int n = digitSum.size();
        if (!flag) {
            flag = 1;
            b.resize(100);
            for (int i = 0; i <= 5000; ++i) {
                int v = i;
                while (v) {
                    a[i] += v % 10;
                    v /= 10;
                }
                b[a[i]].push_back(i);
            }
        }
        vll dp(n, vl(5001));
        for (int v : b[digitSum[0]]) dp[0][v] = 1;
        for (int i = 1; i < n; ++i) {
            int p = 0, pre = digitSum[i - 1], cur = digitSum[i];
            ll sum = 0;
            if (b[cur].empty()) return 0;
            for (int v : b[cur]) {
                while (p < b[pre].size() && b[pre][p] <= v) sum += dp[i - 1][b[pre][p++]];
                dp[i][v] = sum % MOD;
            }
        }
        ll ans = 0;
        for (int v : b[digitSum[n - 1]]) ans += dp[n - 1][v];
        return ans % MOD;
    }
};