// https://leetcode.cn/problems/maximum-of-absolute-value-expression/
// 求解三维曼哈顿距离的最大值，考虑把绝对值符号拆解掉然后就可以得到所有的符号情况，然后枚举符号情况就可以了


class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
    	const int d[8][3] = {
    		{1, 1, 1},
    		{1, 1, -1},
    		{1, -1, 1},
    		{1, -1, -1},
    		{-1, 1, 1},
    		{-1, 1, -1},
    		{-1, -1, 1},
    		{-1, -1, -1}
    	};

    	vector<int> mx(8, INT_MIN);

    	int n = arr1.size();
    	for (int i = 0; i < 8; ++i) {
    		for (int j = 0; j < n; ++j) {
    			mx[i] = max(mx[i], d[i][0] * arr1[j] + d[i][1] * arr2[j] + d[i][2] * j);
    		}
    	}
    	int ans = 0;
    	for (int i = 0; i < 8; ++i) {
    		for (int j = 0; j < n; ++j) {
    			ans = max(ans, mx[i] - d[i][0] * arr1[j] - d[i][1] * arr2[j] - d[i][2] * j);
    		}
    	}
    	return ans;
    }
};