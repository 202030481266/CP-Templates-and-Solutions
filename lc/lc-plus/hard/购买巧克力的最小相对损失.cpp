// 一道困难的二分题目，主要是查找最小的n-m个与给定值最小的绝对值元素
// 很容易发现要使用排序 + 二分，但是具体的二分实现很复杂
class Solution {
public:
    vector<long long> minimumRelativeLosses(vector<int>& prices, vector<vector<int>>& queries) {
        int n = prices.size();
        sort(prices.begin(), prices.end());
        vector<long long> psum(n + 1);
        for (int i = 0; i < n; i++) {
            psum[i + 1] = psum[i] + prices[i];
        }

        vector<long long> res;
        for (auto &q : queries) {
            int k = q[0], m = q[1];
            if (m == n) {
                int x = upper_bound(prices.begin(), prices.end(), k) - prices.begin();
                res.push_back(psum[x] + (long long) k * (n - x) * 2 - (psum[n] - psum[x]));
                continue;
            }

            int need = n - m, idx = m;
            int lo = 0, hi = m - 1;
            while (lo <= hi) {
                int mid = (lo + hi) >> 1;
                if (abs(k - prices[mid]) > abs(prices[mid + need] - k)) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                    idx = mid;
                }
            }
            long long left = psum[idx];
            long long right = (long long) k * (n - idx - need) * 2 - (psum[n] - psum[idx + need]);
            res.push_back(left + right);
        }
        return res;
    }
};

