class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        int n = nums.size(), m = n / 2;
        set<int> buck[20];
        int tot = accumulate(nums.begin(), nums.end(), 0);
        for (int i = 0; i < (1 << m); ++i) {
            int tmp = 0, cnt = 0;
            for (int j = 0; j < m; ++j) 
                if ((i >> j) & 1) {
                    tmp += nums[j]; 
                    ++cnt;
                }
            buck[cnt].emplace(tmp * 2);
        }
        int ans = INT_MAX;
        for (int i = 0; i < (1 << m); ++i) {
            int tmp = 0, cnt = 0;
            for (int j = 0; j < m; ++j) {
                if ((i >> j) & 1) {
                    tmp += nums[j + m];
                    ++cnt;
                }
            }
            int M = tot - tmp * 2;
            auto it = buck[m - cnt].lower_bound(M);
            if (it != buck[m - cnt].end()) ans = min(ans, *it - M);
            if (it != buck[m - cnt].begin()) ans = min(ans, M - *prev(it));
        }
        return ans;
    }
};