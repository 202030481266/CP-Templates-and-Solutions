// https://leetcode.cn/problems/furthest-building-you-can-reach/
// 反悔贪心的技巧


class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
    	priority_queue<int, vector<int> , greater<int>> q;

    	int n = heights.size();
    	for (int i = 1; i < n; ++i) {
    		if (heights[i] <= heights[i - 1]) continue;
    		int s = heights[i] - heights[i - 1];
    		if (ladders > 0) {
    			// 优先使用梯子
    			--ladders;
    			q.push(s);
    		}
    		else {
    			if (q.empty() || q.top() >= s) {
    				// 没有梯子可以换
    				if (bricks < s) return i - 1;
    				bricks -= s;
    			}
    			else {
    				int k = q.top();
    				if (bricks < k) return i - 1;
    				q.pop();
    				bricks -= k;
    				q.push(s);
	    		}
    		}
    	}
    	return n - 1;
    }
};