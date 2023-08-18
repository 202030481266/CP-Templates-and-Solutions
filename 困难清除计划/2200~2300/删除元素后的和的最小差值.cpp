// https://leetcode.cn/problems/minimum-difference-in-sums-after-removal-of-elements/



class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
    	long long n = nums.size(), m = n / 3, pre[n], suf[n], sum = 0;
    	memset(pre, 0, sizeof(pre));
    	memset(suf, 0, sizeof(suf));
    	priority_queue<int, vector<int>, greater<int>> q1;
    	priority_queue<int, vector<int>, less<int>> q2;
    	for (int i = 0; i < m; ++i) q2.emplace(nums[i]), sum += nums[i];
    	pre[m - 1] = sum;
    	for (int i = m; i < 2 * m; ++i) {
    		if (q2.top() > nums[i]) {
    			sum -= q2.top();
    			sum += nums[i];
    			q2.pop();
    			q2.emplace(nums[i]);
    		}
    		pre[i] = sum;
    	}
    	sum = 0;
    	for (int i = n - 1; i >= n - m; --i) q1.emplace(nums[i]), sum += nums[i];
    	suf[n - m] = sum;
    	for (int i = n - m - 1; i >= n - 2 * m; --i) {
    		if (q1.top() < nums[i]) {
    			sum -= q1.top();
    			sum += nums[i];
    			q1.pop();
    			q1.emplace(nums[i]);
    		}
    		suf[i] = sum;
    	}
    	long long ans = 2e10;
    	for (int i = m - 1; i < 2 * m; ++i) ans = min(ans, pre[i] - suf[i + 1]);
    	return ans;
    }
};