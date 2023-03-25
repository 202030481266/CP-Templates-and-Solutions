// https://leetcode.cn/problems/maximum-equal-frequency/



class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
    	int n = nums.size();

    	vector<int> cnt(100010);
    	vector<int> sum(n + 1);
    	int maxx = 0, ans = 0;

    	for (int i = 0; i < n; ++i) {
    		++cnt[nums[i]];
    		--sum[cnt[nums[i]] - 1];
    		++sum[cnt[nums[i]]];
    		maxx = max(maxx, cnt[nums[i]]);
    		if (maxx == 1) {
    			ans = i + 1;
    		}
    		if (maxx * sum[maxx] == i) ans = i + 1;
    		if ((maxx - 1) * (sum[maxx - 1] + 1) == i) ans = i + 1;
    	}
    	return ans;
    }
};