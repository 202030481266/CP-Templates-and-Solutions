class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        // 有一个十分巧妙非常关键的转换：乘积->加减
        // a1+a2+a3+...+aj>=j*mid等价于
        // (a1-mid)+(a2-mid)+(a3-mid)+...+(aj-mid)>=0
        double l = *min_element(nums.begin(), nums.end()) * 1.0;
        double r = *max_element(nums.begin(), nums.end()) * 1.0;
        double ans = 0, eps = 1e-5;
        int n = nums.size();
        vector<double> sum(n + 1);
        auto check = [&](double mid) -> bool {
            sum[0] = 0;
            for (int i = 0; i < n; ++i) {
                sum[i + 1] = sum[i] + nums[i] * 1.0 - mid;
            }
            double mn = 0;
            for (int i = k; i <= n; ++i) {
                if (sum[i] - mn >= 0) return true;
                mn = min(mn, sum[i - k + 1]);
            }
            return false;
        };
        while (l + eps < r) {
            double mid = (l + r) / 2;
            if (check(mid)) l = mid;
            else r = mid;
        }
        return l;
    }
};