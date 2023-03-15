// https://leetcode.cn/problems/maximal-network-rank/



class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
    	vector<int> g[n];
    	vector cnt(n, vector<int>(n));

    	for (auto c : roads) {
    		g[c[0]].emplace_back(c[1]);
    		g[c[1]].emplace_back(c[0]);
    		cnt[c[0]][c[1]] = cnt[c[1]][c[0]] = 1;
    	}
    	int ans = 0;
    	for (int i = 0; i < n; ++i)
    		for (int j = i + 1; j < n; ++j) {
    			ans = max(ans, (int)g[i].size() + (int)g[j].size() - cnt[i][j]);
    		}
    	return ans;
    }
};