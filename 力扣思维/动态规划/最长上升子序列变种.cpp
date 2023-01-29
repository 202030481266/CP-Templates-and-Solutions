// 技巧：按照一个维度排序，然后进行普通的最长上升子序列dp即可
// https://leetcode.cn/problems/pile-box-lcci/submissions/395958685/


class Solution {
public:
    int pileBox(vector<vector<int>>& box) {
        sort(box.begin(), box.end(), [&](vector<int> &x, vector<int> &y) {
            if (x[0] != y[0]) return x[0] < y[0];
            else return x[1] < y[1];
        });
        int n = box.size();
        vector<int> dp(n + 1);

        auto f = [&](vector<int>& x, vector<int>& y) {
            // judge  x > y
            return x[0] > y[0] && x[1] > y[1] && x[2] > y[2];
        };

        dp[1] = box[0][2]; 
        for (int i = 2; i <= n; i++) {
            dp[i] = box[i - 1][2];
            for (int j = 1; j < i; j++) {
                if (f(box[i-1], box[j-1])) {
                    dp[i] = max(dp[i], dp[j] + box[i - 1][2]);
                }
            }
        }
        for (int i = 1; i <= n; i++) cout << dp[i] << ' ';
        return *max_element(dp.begin(), dp.end());
    }
};