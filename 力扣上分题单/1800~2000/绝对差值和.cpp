// https://leetcode.cn/problems/minimum-absolute-sum-difference/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
    	vector<int> a(nums1.begin(), nums1.end());
    	sort(a.begin(), a.end());

    	long long sum = 0;
    	int n = a.size();
    	for (int i = 0; i < n; ++i) {
    		sum += abs(nums1[i] - nums2[i]);
    	}
    	if (sum == 0) return 0;
    	long long ans = sum;
    	for (int i = 0; i < n; ++i) {
    		long long temp = sum - abs(nums1[i] - nums2[i]);
    		auto it = lower_bound(a.begin(), a.end(), nums2[i]);
    		if (it == a.end()) {
    			ans = min(ans, temp + nums2[i] - a.back());
    		}
    		else if (it == a.begin()) {
    			ans = min(ans, temp + a[0] - nums2[i]);
    		}
    		else {
    			int k = min(*it - nums2[i], nums2[i] - *prev(it));
    			ans = min(ans, temp + k);
    		}
    	}
    	return ans % mod;
    }
};