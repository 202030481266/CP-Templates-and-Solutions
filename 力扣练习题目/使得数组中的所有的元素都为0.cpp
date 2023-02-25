class Solution {
public:
    int minimumOperations(vector<int>& nums) {
    	sort(nums.begin(), nums.end());
    	int a = 0;
    	int ans = 0;
    	int n = nums.size();
    	for (int i = 0; i < n; ++i) {
    		if (nums[i] - a > 0) {
    			a += (nums[i] - a);
    			++ans;
    			if (a >= nums[n - 1]) return ans;
    		}
    	}
    	return ans;
    }
};