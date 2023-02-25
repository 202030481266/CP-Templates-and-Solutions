class Solution {
public:
    static constexpr int mod = 1000000007;
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
    map<int, int> factorize(int n) {
        map<int, int> factors;
        for (int d = 2; d * d <= n; d++) {
            while (n % d == 0) {
                ++factors[d];
                n /= d;
            }
        }
        if (n > 1) {
            ++factors[n];
        }
        return factors;
    }
    int pow_mod(int x, int n) {
        int res = 1;
        for (long long p = x; n > 0; n >>= 1, p = (p * p) % mod)
            if ((n & 1) != 0)
                res = (int)(res * p % mod);
        return res;
    }
    int squareFreeSubsets(vector<int>& nums) {
        auto primes = generate_primes_linear_time(30);

        // 只有十位质数，因此可以暴力统计，使用一个整数来表示状态
        // 总共只有4024种状态

        vector<int> a;
        int cnt_1 = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if(nums[i] == 1) ++cnt_1;
            else a.emplace_back(nums[i]);
        }

        auto encode = [&](map<int,int> factors) -> int {
            vector<int> pos;
            for (auto it : factors) {
                for (int i = 0; i < 10; ++i) 
                    if (it.first == primes[i]) {
                        pos.emplace_back(i);
                        break;
                    }
            }
            int res = 0;
            for (auto c : pos)
                res |= (1 << c);
            return res;
        };

        vector<long long> dp((1 << 10), 0);
        dp[0] = 1;
        int n = a.size();
        for (int i = 0; i < n; ++i) {
            auto factors = factorize(a[i]);
            int status = encode(factors);

            bool flag = true;
            for (auto it : factors) {
                if (it.second >= 2) flag = false;
            }
            if (!flag) continue;

            for (int i = 0; i < dp.size(); ++i) {
                if ((i & status) == 0) {
                    int S = (i | status);
                    dp[S] = (dp[S] + dp[i]) % mod;
                }
            }
        }

        long long ans = 0;
        for (int i = 1; i < dp.size(); ++i) 
            ans = (ans + dp[i]) % mod;
        if (cnt_1 > 0)
            ans = (pow_mod(2, cnt_1) * ans + (pow_mod(2, cnt_1) - 1) % mod) % mod;
        return ans;
    }
};