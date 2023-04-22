class Solution {
    int f[1010][1010];
public:
    int longestArithSeqLength(vector<int>& nums) {
        memset(f, 0, sizeof(f));
        int n = nums.size(), ans = 0;
        for (int i = 0; i < n; ++i) 
            for (int j = i - 1; j >= 0; --j) {
                int tmp = nums[i] - nums[j] + 500;
                f[i][tmp] = max(f[i][tmp], f[j][tmp] + 1);
                ans = max(ans, f[i][tmp]);
            }
        return ans + 1;
    }
};