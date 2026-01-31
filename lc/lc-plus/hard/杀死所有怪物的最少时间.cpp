// 1600ms
class Solution {
public:
    using ll = long long;
    long long minimumTime(vector<int>& power) {
        int n = power.size();
        vector<int> arr;

        ll dp[n + 1][1 << n];
        memset(dp, 0x3f, sizeof(dp));
        memset(dp[0], 0, sizeof(dp[0]));
        
        for (int i = 1; i <= n; ++i) {
            for (int s = 0; s < (1 << n); ++s) {
                for (int j = 0; j < n; ++j) {
                    if ((s >> j) & 1) {
                        dp[i][s] = min(dp[i][s], dp[i - 1][s ^ (1 << j)] + (power[i - 1] - 1) / (j + 1) + 1);
                    }
                }
            }
        }
        return dp[n][(1 << n) - 1];
    }
};


// 考虑状态优化的时候可以有一个技巧：一个状态信息是否可以由状态其他信息推导而来或者说对于某一个特定的状态，该值是固定的。
// 这个状态设计实际上还是有压缩的空间，因为我们用了01串表示的是一个，那么我们也可以反过来，将01串表示数组还有哪些数字可用
// 这个时候的状态对应的gain值就是 状态中的0个数 + 1
// 148ms
class Solution {
public:
    using ll = long long;
    long long minimumTime(vector<int>& power) {
        int n = power.size();
        vector<int> arr;

        ll dp[1<<n];
        memset(dp, 0x3f, sizeof(dp));
        // dp[s]=dp[s^(1<<j)]
        dp[0] = 0;
        for (int s = 0; s < (1 << n); ++s) {
            int gain = n + 1;
            for (int i = 0; i < n; ++i)
                if ((s >> i) & 1) --gain;
            for (int i = 0; i < n; ++i) {
                if ((s >> i) & 1) {
                    dp[s] = min(dp[s], dp[s ^ (1<<i)] + (power[i] - 1) / gain + 1);
                }
            }
        }
        return dp[(1<<n)-1];
    }
};