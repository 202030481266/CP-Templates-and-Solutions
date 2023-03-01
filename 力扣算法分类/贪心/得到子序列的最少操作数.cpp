// https://leetcode.cn/problems/minimum-operations-to-make-a-subsequence/
// 使用优化的lcs技巧进行动态规划，考虑贪心，答案就是 n-LCS



class Solution {
public:
    int minOperations(vector<int>& target, vector<int>& arr) {
    	int n = target.size(), m = arr.size();

    	unordered_map<int,int> a;
    	for (int i = 0; i < n; ++i)
    		a[target[i]] = i;
    	vector<int> b;
    	for (int i = 0; i < m; ++i) 
    		if (a.count(arr[i])) b.emplace_back(a[arr[i]]);

    	// LIS nlogn
    	vector<int> g(b.size() + 1, INT_MAX);
    	vector<int> dp(b.size() + 1);
    	int maxx = 0;
    	for (int i = 0; i < b.size(); ++i) {
    		int j = lower_bound(g.begin(), g.end(), b[i]) - g.begin();
    		dp[i] = j + 1;
    		if (maxx < dp[i])
    			maxx = dp[i];
    		g[j] = b[i];
    	}
    	return n - maxx;
    }
};