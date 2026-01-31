class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        // dp[i] = min(sum[i] - sum[x], dp[x]), (x, i]
        // 二分dp或者二分答案
        int l = *max_element(weights.begin(), weights.end()) - 1;
        int r = accumulate(weights.begin(), weights.end(), 0);
        auto check = [&](int val) -> bool {
            int res = 0, n = weights.size(), i = 0, s = 0;
            // 这里的分组循环十分不好写
            // 建议这里的逻辑使用开区间然后分类讨论
            while (i < n) {
                while (i < n && s < val) s += weights[i++];
                // [i, p)
                if (s > val) ++res, --i, s = 0;
                else if (s == val) ++res, s = 0;
            }
            if (s > 0) ++res; // [i, n)
            return res <= days;
        };

        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid;
            else l = mid;
        }
        
        return r;
    }
};