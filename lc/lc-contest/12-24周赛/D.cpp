class Solution {
    const int MOD = 1e9 + 7;
public:
    int countPartitions(vector<int> &nums, int k) {
        if (accumulate(nums.begin(), nums.end(), 0L) < k * 2) return 0;
        int ans = 1, f[k]; memset(f, 0, sizeof(f));
        f[0] = 1;
        for (int x : nums) {
            ans = ans * 2 % MOD;
            for (int j = k - 1; j >= x; --j)
                f[j] = (f[j] + f[j - x]) % MOD;
        }
        for (int x : f)
            ans = (ans - x * 2 % MOD + MOD) % MOD; // 保证答案非负
        return ans;
    }
};

