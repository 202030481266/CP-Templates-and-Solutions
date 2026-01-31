// https://leetcode.cn/problems/number-of-submatrices-that-sum-to-target/
// 思想： 降维，技巧： 前缀和 + 哈希表


class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    	int n = matrix.size(), m = matrix[0].size(), col[m + 1][n + 1], sum[m + 1];
    	memset(col, 0, sizeof(col));
		memset(sum, 0, sizeof(sum));
    	for (int i = 1; i <= m; ++i)
    		for (int j = 1; j <= n; ++j) col[i][j] = col[i][j - 1] + matrix[j - 1][i - 1];
    	// 枚举其中的两个行，这种题目和一维的很相似，核心思想在于降维
    	int res = 0;
    	for (int i = 1; i <= n; ++i)
    		for (int j = i; j <= n; ++j) {
    			for (int k = 1; k <= m; ++k) sum[k] = col[k][j] - col[k][i - 1] + sum[k - 1];
    			unordered_map<int, int> h;
				++h[0];
    			for (int r = 1; r <= m; ++r) {
    				res += h[sum[r] - target];
    				++h[sum[r]];
    			}
    		}
    	return res;
    }
};