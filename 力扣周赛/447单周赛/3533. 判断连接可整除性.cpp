#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

int f[15][80];
int dp[1<<13][100];
int len[1<<13];

class Solution {
public:
    vector<int> concatenatedDivisibility(vector<int>& nums, int k) {
        int N = 0, n = nums.size();
        sort(nums.begin(), nums.end());
        vector<string> a;
        for (int&v : nums) {
            a.emplace_back(to_string(v));
            N += a.back().size();
        }
        for (int i = 0; i < n; ++i) {
            int m = a[i].size();
            f[i][m-1] = nums[i] % k;
            for (int j = m; j < N; ++j) {
                f[i][j] = f[i][j-1] * 10 % k;
            }
        }
        for (int i = 0; i < (1<<n); ++i) {
            for (int j = 0; j < k; ++j) dp[i][j] = 0;
            len[i] = 0;
            for (int j = 0; j < n; ++j) {
                if (i & (1<<j)) len[i] += a[j].size();
            }
        }
        dp[0][0] = 1;
        for (int i = 1; i < (1<<n); ++i) {
            for (int j = 0; j < n; ++j) {
                if (i & (1<<j)) {
                    int tmp = f[j][len[i]-1];
                    for (int x = 0; x < k; ++x) {
                        dp[i][x] |= dp[i^(1<<j)][((x-tmp)%k+k)%k];
                    }
                }
            }
        }
        vector<int> ans;
        int cur = (1<<n)-1, sum = 0;
        if (!dp[cur][0]) return {};
        while (cur) {
            for (int i = 0; i < n; ++i) {
                if (cur & (1<<i)) {
                    int tmp = f[i][len[cur]-1];
                    if (dp[cur^(1<<i)][((sum-tmp)%k+k)%k]) {
                        ans.push_back(nums[i]);
                        sum = ((sum-tmp)%k+k)%k;
                        cur ^= (1<<i);
                        break;
                    }
                }
            }
        }
        return ans;
    }
};