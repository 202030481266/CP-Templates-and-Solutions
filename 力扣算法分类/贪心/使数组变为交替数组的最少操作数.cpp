// https://leetcode.cn/problems/minimum-operations-to-make-the-array-alternating/



class Solution {
public:
    int minimumOperations(vector<int>& nums) {
    	int n = nums.size();

    	if (n == 1) return 0;

    	vector<int> a(100001);
    	vector<int> b(100001);

    	for (int i = 0; i < n; i += 2) 
    		++a[nums[i]];
    	for (int i = 1; i < n; i += 2)
    		++b[nums[i]];
    	int x = 0, y = 0, yy = 0, xx = 0;
    	for (int i = 0; i < n; i += 2)
    		if (a[nums[i]] > x) {
    			xx = nums[i];
    			x = a[nums[i]];
    		}
    	for (int i = 1; i < n; i += 2)
    		if (b[nums[i]] > y) {
    			yy = nums[i];
    			y = b[nums[i]];
    		}
    	if (yy != xx) return n - x - y;

    	// a choose xx
    	y = 0, yy = 0;
    	for (int i = 1; i < n; i += 2)
    		if (b[nums[i]] > y && nums[i] != xx) {
    			yy = nums[i];
    			y = b[nums[i]];
    		}
    	int ans = n - x - y;
    	// b choose xx;
    	y = b[xx], yy = xx;
    	x = 0, xx = 0;
    	for (int i = 0; i < n; i += 2) 
    		if (a[nums[i]] > x && nums[i] != yy) {
    			xx = nums[i];
    			x = a[nums[i]];
    		}
    	return min(n - x - y, ans);
    }
};