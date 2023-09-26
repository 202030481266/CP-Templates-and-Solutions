class Solution {
    unordered_set<long long> is_valid;
    unordered_map<int, long long> cnt;
public:
    long long maximumSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            int tmp = i + 1;
            int x = 1;
            for (int j = 2; j * j <= tmp; ++j) {
                int cnt = 0; 
                while (tmp % j == 0) {
                    ++cnt;
                    tmp /= j;
                }
                if (cnt & 1) x *= j;
            }
            if (tmp > 1) x *= tmp;
            cnt[x] += nums[i];
        }
        long long ans = 0;
        for (auto [k, v] : cnt) ans = max(ans, v);
        return ans;
    }
};