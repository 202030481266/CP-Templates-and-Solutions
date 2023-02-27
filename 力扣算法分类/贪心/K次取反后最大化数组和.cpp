// https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/



class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
    	vector<int> a;
    	int sum = 0;
    	int b = INT_MAX;

    	for (auto c : nums) {
    		if (c < 0) a.emplace_back(c); 
    		else sum += c, b = min(b, c);
    	}
    	sort(a.begin(), a.end());
    	int n = a.size();

    	if (k <= n) {
    		for (int i = 0; i < k; ++i) sum -= a[i];
    		for (int i = k; i < n; ++i) sum += a[i];
    	}
    	else {
    		// k > n;
    		for (int i = 0; i < n; ++i) sum -= a[i];
    		if (b > 0 && ((k - n) & 1)) {
    			if (n > 0) b = min(b, -a[n - 1]);
    			sum -= 2 * b;
    		} 
    	}
    	return sum;
    }
};