const int mod = 1e9 + 7;
class Solution {
public:
    int sumOfPowers(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> arr;
        
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                arr.push_back(abs(nums[j] - nums[i]));
        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());

        int m = arr.size();
        vector dp(n, vector(m, vector<int>(k + 1)));
        for (int i = 1; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                // (i, j)
                int t = lower_bound(arr.begin(), arr.end(), abs(nums[i] - nums[j])) - arr.begin();
                dp[i][t][2] += 1;
                for (int x = 3; x <= k; ++x) {
                    for (int y = t; y < m; ++y)
                        dp[i][t][x] = (dp[i][t][x] + dp[j][y][x - 1]) % mod;
                    for (int y = 0; y < t; ++y)
                        dp[i][y][x] = (dp[i][y][x] + dp[j][y][x - 1]) % mod;
                }
            }
        }

        // for (int i = 0; i < n; ++i) {
        //     for (int j = 0; j < m; ++j) {
        //         for (int x = 2; x <= k; ++x) {
        //             cout << i << ' ' << arr[j] << ' ' << x << ' ' << dp[i][j][x] << endl;
        //         }
        //     }
        // }
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                ans = (ans + arr[j] * 1ll * dp[i][j][k] % mod) % mod;
        }
        return ans;
    }
};