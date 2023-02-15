// https://leetcode.cn/problems/next-greater-element-ii/
// 下一个最大元素的变种，环形数组
// 考虑拼接数组


class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
    	int n = nums.size();
    	vector<int> a(2 * n);
    	vector<int> ans(2 * n, -1);

    	for (int i = 0; i < 2 * n; ++i) a[i] = nums[i % n];
    	stack<int> s;
    	for (int i = 0; i < 2 * n; ++i) {
    		while (!s.empty() && a[s.top()] < a[i]) {
    			int u = s.top();
    			s.pop();
    			ans[u] = a[i];
    		}
    		s.push(i);
    	}
    	vector<int> res(ans.begin(), ans.begin() + n);
    	return res;
    }
};