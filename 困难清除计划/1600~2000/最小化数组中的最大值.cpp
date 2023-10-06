// https://leetcode.cn/problems/minimize-maximum-of-array/



class Solution {
public:
    int minimizeArrayValue(vector<int>& nums) {
    	int n = nums.size();
    	vector<long long> a(nums.begin(), nums.end());
    	long long sum = 0;
        for (int i = n - 1; i >= 0; --i)
            sum += a[i];
    	for (int i = n - 1; i >= 1; --i) {
    		if (a[i] == 0) continue;
    		long long x = sum / (i + 1), y = sum % (i + 1);
    		if (y > 0) ++x;
    		if (a[i] > x) {
    			a[i - 1] += (a[i] - x);
    			a[i] = x;
    		}
    		sum -= a[i];
    	}
    	return *max_element(a.begin(), a.end());
    }
};