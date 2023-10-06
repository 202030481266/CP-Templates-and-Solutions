// https://leetcode.cn/problems/find-the-longest-valid-obstacle-course-at-each-position/



class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
    	int n = obstacles.size();

    	vector<int> g(n + 1, INT_MAX);
    	vector<int> dp(n, 0);

    	for (int i = 0; i < n; ++i) {
    		int j = upper_bound(g.begin(), g.end(), obstacles[i]) - g.begin();
    		dp[i] = j + 1;
    		g[j] = obstacles[i];
    	}
    	return dp;
    }
};