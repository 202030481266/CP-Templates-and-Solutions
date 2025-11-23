constexpr static int MOD = 1'000'000'007;
constexpr static int MAX_N = 100'001;
int pow2[MAX_N];

int init = [] {
    // 预处理 2 的幂
    pow2[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        pow2[i] = pow2[i - 1] * 2 % MOD;
    }
    return 0;
}();

class Solution {
public:
    int countEffective(vector<int>& nums) {
        int or_ = reduce(nums.begin(), nums.end(), 0, bit_or<>());
        int w = bit_width((uint32_t) or_);

        vector<int> f(1 << w);
        for (int x : nums) {
            f[x]++;
        }
        for (int i = 0; i < w; i++) {
            if ((or_ >> i & 1) == 0) { // 优化：or_ 中是 0 但 s 中是 1 的 f[s] 后面容斥用不到，无需计算
                continue;
            }
            for (int s = 0; s < (1 << w); s++) {
                if (s >> i & 1)
                    f[s] += f[s ^ (1 << i)];
            }
        }
        // 计算完毕后，f[s] 表示 nums 中的是 s 的子集的元素个数

        long long ans = pow2[nums.size()]; // 所有子序列的个数
        // 枚举 or 的所有子集（包括空集）
        int sub = or_;
        do {
            int sign = popcount((uint32_t) or_ ^ sub) % 2 ? -1 : 1;
            ans -= sign * pow2[f[sub]];
            sub = (sub - 1) & or_;
        } while (sub != or_);
        return (ans % MOD + MOD) % MOD; // 保证结果非负
    }
};


// 其实不必正难则反，本质就是容斥原理

class Solution {
public:
    int countEffective(vector<int>& nums) {
        int or_ = reduce(nums.begin(), nums.end(), 0, bit_or<>());
        int w = bit_width((uint32_t) or_);

        vector<int> f(1 << w);
        for (int x : nums) {
            f[x]++;
        }
        for (int i = 0; i < w; i++) {
            if ((or_ >> i & 1) == 0) { // 优化：or_ 中是 0 但 s 中是 1 的 f[s] 后面容斥用不到，无需计算
                continue;
            }
            for (int s = 0; s < (1 << w); s++) {
                if (s >> i & 1)
                    f[s] += f[s ^ (1 << i)];
            }
        }
        // 计算完毕后，f[s] 表示 nums 中的是 s 的子集的元素个数

        long long ans = 0;
        for (int i = or_; i; i = (i - 1) & or_) {
            int one = popcount(1u * i);
            if (one & 1) ans = (ans + pow2[f[or_ ^ i]]) % MOD;
            else ans = ((ans - pow2[f[or_ ^ i]]) % MOD + MOD) % MOD;
        }
        return ans;
    }
};