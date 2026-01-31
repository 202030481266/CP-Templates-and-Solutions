// https://leetcode.cn/problems/maximum-score-of-a-node-sequence/



class Solution {
	typedef pair<int, int> pii;
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
    	// 长度为四的权值最大的简单路径
    	int n = scores.size();
    	set<pair<int, int>> s[n];  // 不可能出现重复
    	for (auto &c : edges) {
    		s[c[0]].emplace(scores[c[1]], c[1]);
    		s[c[1]].emplace(scores[c[0]], c[0]);
    	}
    	int ans = -1;
    	for (auto &c : edges) {
    		// 删边
    		s[c[0]].erase(pii{scores[c[1]], c[1]});
    		s[c[1]].erase(pii{scores[c[0]], c[0]});
    		if (!s[c[0]].empty() && !s[c[1]].empty()) {
    			int tmp = 0;
    			if (s[c[0]].rbegin()->second != s[c[1]].rbegin()->second) {  // 最大值的点不同
    				tmp = s[c[0]].rbegin()->first + s[c[1]].rbegin()->first;
    			}
    			else {
    				// 最大值的点相同，那么判断两个点是否有第二大，以及谁的第二大的点更大
    				int sc = 0;
    				if (s[c[0]].size() >= 2) sc = max(sc, prev(prev(s[c[0]].end()))->first);
    				if (s[c[1]].size() >= 2) sc = max(sc, prev(prev(s[c[1]].end()))->first);
    				if (sc > 0) {  // 表明他们至少有一个其他的节点
    					tmp = sc + s[c[0]].rbegin()->first;
    				}
    			}
    			if (tmp) ans = max(ans, tmp + scores[c[0]] + scores[c[1]]);
    		}
    		// 加边
    		s[c[0]].emplace(scores[c[1]], c[1]);
    		s[c[1]].emplace(scores[c[0]], c[0]);
    	}
    	return ans;
    }
};