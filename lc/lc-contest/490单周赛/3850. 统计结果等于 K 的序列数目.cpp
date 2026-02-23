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


static constexpr int factor[] = {2, 3, 5};
static constexpr int fac[7][3] = {
    {0, 0, 0}, // 0
    {0, 0, 0}, // 1
    {1, 0, 0}, // 2
    {0, 1, 0}, // 3
    {2, 0, 0}, // 4
    {0, 0, 1}, // 5
    {1, 1, 0}, // 6
};

int dp[2][100][44][44];

class Solution {
public:
    int countSequences(vector<int>& nums, long long k) {
        int n = nums.size();
        vector<int> cnt(3); // 2, 3, 5
        for (int i = 0; i < 3; ++i) {
            while (k % factor[i] == 0) {
                ++cnt[i];
                k /= factor[i];
            }
        }
        if (k > 1) return 0;
        vector<int> have(3);
        for (int v : nums) {
            for (int i = 0; i < 3; ++i) have[i] += fac[v][i];
        }
        if (cnt[0] > have[0] || cnt[1] > have[1] || cnt[2] > have[2]) return 0;
        int one = 0;
        int pre = 0, cur = 1;
        memset(dp[pre], 0, sizeof(dp[pre]));
        dp[pre][40][20][20] = 1;
        for (int x = 0; x < n; ++x) {
            if (nums[x] == 1) {
                ++one;
                continue;
            }
            int a = fac[nums[x]][0];
            int b = fac[nums[x]][1];
            int c = fac[nums[x]][2];
            for (int i = -2 * n; i <= n * 2; ++i) {
                for (int j = -n; j <= n; ++j) {
                    for (int k = -n; k <= n; ++k) {
                        dp[cur][i + 40][j + 20][k + 20] = dp[pre][i + 40][j + 20][k + 20];
                        if (i + a <= 2 * n && j + b <= n && k + c <= n) {
                            dp[cur][i + 40][j + 20][k + 20] += dp[pre][i + a + 40][j + b + 20][c + k + 20];
                        }
                        if (i - a >= -2 * n && j - b >= -n && k - c >= -n) {
                            dp[cur][i + 40][j + 20][k + 20] += dp[pre][i - a + 40][j - b + 20][k - c + 20];
                        }
                    }
                }
            }
            swap(pre, cur);
        }
        return dp[pre][cnt[0] + 40][cnt[1] + 20][cnt[2] + 20] * (int)pow(3, one);
    }
};