class Solution {
public:
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) {
        int n = colsum.size();
        auto ans = vector(2, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            if (colsum[i] == 2) {
                if (upper == 0 || lower == 0) return {};
                ans[0][i] = ans[1][i] = 1;
                --upper;
                --lower;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (colsum[i] == 1) {
                if (upper) ans[0][i] = 1, ans[1][i] = 0, --upper;
                else if (lower) ans[0][i] = 0, ans[1][i] = 1, --lower;
                else return {};
            }
        }
        if (lower != 0 || upper != 0) return {};
        return ans;
    }
};