#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

int dp[1001];

class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), a[11][n + 1];
        auto check = [&](int k) -> bool {
            memset(a, 0, sizeof(a));
            for (int i = 0; i < k; ++i) {
                int l = queries[i][0], r = queries[i][1], val = queries[i][2];
                a[val][l]++, a[val][r + 1]--;
            }
            for (int i = 1; i <= 10; ++i) {
                for (int j = 1; j < n; ++j) {
                    a[i][j] += a[i][j - 1];
                }
            }
            for (int i = 0; i < n; ++i) {
                if (nums[i] == 0) continue;
                for (int j = 0; j <= nums[i]; ++j) dp[j] = 0;
                dp[0] = 1;
                for (int j = 1; j <= 10 && !dp[nums[i]] && j <= nums[i]; ++j) {
                    if (a[j][i] == 0) continue;
                    int k = a[j][i];
                    for (int x = nums[i]; x > nums[i] - j; --x) {
                        int cnt = 0, r = 0;
                        while (x - r * j >= 0 && r <= k) {
                            cnt += dp[x - r * j];
                            ++r;
                        }
                        for (int y = 0; x - y * j >= 0; ++y) {
                            int res = (cnt > 0);
                            cnt -= dp[x - y * j]; 
                            if (x - r * j >= 0) {
                                cnt += dp[x - r * j];
                                ++r;
                            }
                            dp[x - y * j] = res;
                        }
                    }
                }
                if (!dp[nums[i]]) return false;
            }
            return true;
        };
        int l = -1, r = queries.size() + 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid;
            else l = mid;
        }
        return (r > (int)queries.size() ? -1 : r);
    }
};