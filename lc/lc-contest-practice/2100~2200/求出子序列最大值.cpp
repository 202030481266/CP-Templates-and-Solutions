#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

int dp[1<<7];

class Solution {
public:
    int maxValue(vector<int>& nums, int k) {
        // 枚举两个部分的 mask
        int ans = -INF, n = nums.size(), N = 0;
        // 枚举其中的所有mask然后前序和后序
        for (int x = 0; x < n; ++x) {
            N |= nums[x];
        }
        ++N;
        int cnt = 0;
        vector<int> left(N, n), right(N, -1);
        for (int mask = 0; mask < N; ++mask) {
            // 从左到右
            memset(dp, 0x3f, sizeof(dp));
            dp[0] = 0;
            cnt = 0;
            for (int i = 0; i < n; ++i) {
                if ((mask | nums[i]) == mask) {
                    ++cnt;
                    for (int j = mask; j; j = (j-1)&mask) {
                        // 枚举mask的子集
                        if ((j & nums[i]) == nums[i]) {
                            for (int k = nums[i]; k; k = (k-1)&nums[i]) {
                                dp[j] = min(dp[j], dp[j^k]+1);
                            }
                        }
                    }
                    if (cnt >= k && dp[mask] <= k) {
                        left[mask] = i;
                        break;
                    }
                }
            }
            // 从右到左
            memset(dp, 0x3f, sizeof(dp));
            dp[0] = 0;
            cnt = 0;
            for (int i = n-1; i >= 0; --i) {
                if ((mask | nums[i]) == mask) {
                    ++cnt;
                    for (int j = mask; j; j = (j-1)&mask) {
                        if ((j & nums[i]) == nums[i]) {
                            for (int k = nums[i]; k; k = (k-1)&nums[i]) {
                                dp[j] = min(dp[j], dp[j^k]+1);
                            }
                        }
                    }
                    if (cnt >= k && dp[mask] <= k) {
                        right[mask] = i;
                        break;
                    }
                }
            }
        }
        for (int mask1 = 0; mask1 < N; ++mask1) {
            for (int mask2 = 0; mask2 < N; ++mask2) {
                if ((mask1 ^ mask2) > ans && left[mask1] < right[mask2]) {
                    ans = mask1 ^ mask2;
                }
            }
        }
        return ans;
    }
};