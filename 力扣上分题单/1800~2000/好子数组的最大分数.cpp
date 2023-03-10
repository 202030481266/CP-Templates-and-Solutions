// https://leetcode.cn/problems/maximum-score-of-a-good-subarray/



class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
    	int n = nums.size();
    	vector<int> left(n), right(n);
    	stack<int> s;
    	for (int i = 0; i < n; ++i) {
    		while (!s.empty() && nums[s.top()] >= nums[i]) {
    			s.pop();
    		}
    		left[i] = s.empty() ? -1 : s.top();
    		s.push(i);
    	}
    	while (!s.empty()) s.pop();
    	for (int i = n - 1; i >= 0; --i) {
    		while (!s.empty() && nums[s.top()] >= nums[i]) {
    			s.pop();
    		}
    		right[i] = s.empty() ? n : s.top();
    		s.push(i);
    	}
    	int ans = 0;
    	for (int i = 0; i < n; ++i) {
    		if (left[i] + 1 <= k && right[i] - 1 >= k) 
    			ans = max(ans, nums[i] * (right[i] - left[i] - 1));
    	}
    	return ans;
    }
};