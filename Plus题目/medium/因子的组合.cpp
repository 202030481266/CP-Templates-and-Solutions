class Solution {
public:
    void dfs(int pre, int cur, vector<int>& factor, vector<vector<int>>& res) {
        for (int i = pre; i * i <= cur; ++i) {
            if (cur % i == 0) {
                factor.push_back(i);
                vector<int> now(factor.begin(), factor.end());
                now.push_back(cur / i);
                res.push_back(now);
                dfs(i, cur / i, factor, res);
                factor.pop_back();
            }
        }
    }
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> ans;
        vector<int> factor;
        dfs(2, n, factor, ans);
        return ans;
    }
};