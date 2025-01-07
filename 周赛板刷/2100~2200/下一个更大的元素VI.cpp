// https://leetcode.cn/problems/next-greater-element-iv/
// 单调栈的深度理解，思维题


class Solution {
public:
    vector<int> secondGreaterElement(vector<int>& nums) {
    	int n = nums.size();
    	vector<int> ans(n, -1);
    	stack<int> s1, s2;
    	for (int i = 0; i < n; ++i) {
    		while (!s2.empty() && nums[s2.top()] < nums[i]) {
    			ans[s2.top()] = nums[i];
    			s2.pop();
    		}
    		stack<int> tmp;
    		while (!s1.empty() && nums[s1.top()] < nums[i]) {
    			tmp.emplace(s1.top());
    			s1.pop();
    		}
    		s1.emplace(i);
    		while (!tmp.empty()) {
    			s2.emplace(tmp.top());
    			tmp.pop();
    		}
    	}
    	return ans;
    }
};