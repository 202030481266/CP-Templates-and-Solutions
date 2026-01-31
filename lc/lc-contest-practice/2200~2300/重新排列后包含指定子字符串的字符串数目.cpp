
// 重新编码所有的状态然后使用dp（难度较大）
// 尝试过使用组合数学，但是很难去判重，正解是容斥原理

using ll = long long;
const int mod = 1e9 + 7;

ll dp[15];
const int status[] = {0, 1, 2, 4, 5, 6, 8, 9, 10, 12, 13, 14};

class Solution {
public:
    int stringCount(int n) {
        if (n <= 3) return 0;

        memset(dp, 0, sizeof(dp));

        vector<vector<int>> c(12);
        vector<int> a(12, 26);
        for (int j = 0; j < 12; ++j) {
            int i = status[j];
            int cnt_e = (i & 3), cnt_t = ((i >> 2) & 1), cnt_l = ((i >> 3) & 1);
            if (cnt_e) c[j].push_back((i ^ (cnt_e)) | (cnt_e - 1));
            if (cnt_t) c[j].push_back(i ^ (1 << 2));
            if (cnt_l) c[j].push_back(i ^ (1 << 3));
            if (cnt_e < 2) --a[j];
            if (!cnt_t) --a[j];
            if (!cnt_l) --a[j];
        }

        dp[0] = 1;
        for (int i = 0; i < n; ++i)
            for (int j = 11; j >= 0; --j) {
                int s = status[j];
                dp[s] = dp[s] * a[j] % mod;
                for (int& v : c[j])
                    dp[s] = (dp[s] + dp[v]) % mod;
            }

        return dp[14];
    }
};


// 下面是容斥原理的解法，更加容易理解和简单
class Solution {
    const long long MOD = 1e9 + 7;

    long long pow(long long x, int n) {
        long long res = 1;
        for (; n; n /= 2) {
            if (n % 2) {
                res = res * x % MOD;
            }
            x = x * x % MOD;
        }
        return res;
    }

public:
    int stringCount(int n) {
        return ((pow(26, n)
               - pow(25, n - 1) * (75 + n)
               + pow(24, n - 1) * (72 + n * 2)
               - pow(23, n - 1) * (23 + n)) % MOD + MOD) % MOD; // 保证结果非负
    }
};

