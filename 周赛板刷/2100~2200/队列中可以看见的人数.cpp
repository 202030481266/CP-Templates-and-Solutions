// https://leetcode.cn/problems/number-of-visible-people-in-a-queue/
// 对于一个小黄人i他能够看到的所有的人满足左边第一个比他大的人是小黄人i + 右边第一个比他高的小黄人


class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
    	int n = heights.size();
    	vector<int> a(n, -1);
    	vector<int> b(n, -1);
    	vector<int> ans(n, 0);
    	stack<int> s;

    	for (int i = n - 1; i >= 0; --i) {
    		while (!s.empty() && heights[s.top()] < heights[i]) {
    			a[s.top()] = i;
    			s.pop();
    		}
    		s.push(i);
    	}
    	s = stack<int>{};
    	for (int i = 0; i < n; ++i) {
    		while (!s.empty() && heights[s.top()] < heights[i]) {
    			b[s.top()] = i;
    			s.pop();
    		}
    		s.push(i);
    	}
    	for (int i = n - 1; i >= 0; --i) {
    		if (a[i] != -1)
    			++ans[a[i]];
    		if (b[i] != -1)
    			++ans[i];
    	}
    	return ans;
    }
};