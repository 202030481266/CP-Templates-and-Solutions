// 瓶颈在于分解质因数
class Solution {
public:
    vector<int> generate_primes_linear_time(int n) {
        vector<int> lp(n + 1);
        vector<int> primes;
        for (int i = 2; i <= n; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                primes.push_back(i);
            }
            for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= n; ++j)
                lp[i * primes[j]] = primes[j];
        }
        return primes;
    }
    int splitArray(vector<int>& nums) {
        int n = nums.size(), dp[n]; 
        memset(dp, 0x3f, sizeof(dp));

        // 更加快的质因数分解的方法
        // 先找到所有的质数再分解？
        // 好吧，还真是卡了这个，完美卡过
        vector<int> primes = generate_primes_linear_time(1000);

        // 稀疏的质因数
        unordered_map<int, int> h;

        vector<int> fac;
        for (int i = 0; i < n; ++i) {
            fac.clear();
            dp[i] = (i == 0 ? 1 : dp[i - 1] + 1); // 初始化
            // for (long long d = 2; d * d <= nums[i]; ++d) {
                // 最坏情况下，对于所有的
            //     if (nums[i] % d == 0) {
            //         if (h.count(d))
            //             dp[i] = min(dp[i], h[d] + 1);
            //         fac.push_back(d);
            //         while (nums[i] % d == 0) {
            //             nums[i] /= d;
            //         }
            //     }
            // }
            for (int j = 0; (long long)primes[j] * primes[j] <= nums[i]; ++j) {
                if (nums[i] % primes[j] == 0) {
                    if (h.count(primes[j])) dp[i] = min(dp[i], h[primes[j]] + 1);
                    fac.push_back(primes[j]);
                    while (nums[i] % primes[j] == 0) nums[i] /= primes[j];
                }
            }
            if (nums[i] > 1) {
                fac.push_back(nums[i]);
                if (h.count(nums[i]))
                    dp[i] = min(dp[i], h[nums[i]] + 1);
            }
            if (i > 0) {
                for (int& p : fac) {
                    if (h.count(p))
                        h[p] = min(h[p], dp[i - 1]);
                    else h[p] = dp[i - 1];
                }
            }
            else {
                for (int& p : fac) h[p] = 0;
            }
        }
        return dp[n - 1];
    }
};