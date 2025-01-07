// https://leetcode.cn/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/
// 贪心寻找，使用前缀和判断满足条件，哈希表来装之前存在的前缀和
// 技巧：分段前缀和


class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
    	int n = nums.size();

    	// 不是单调递增的数组和
    	// 所以不能使用滑动数组来进行滚动

    	int i = 0; 
    	int ans = 0;
    	while (i < n) {
    		unordered_set<int> s{0};
    		int sum = 0;
    		while (i < n) {
    			sum += nums[i];
    			if (s.find(sum - target) != s.end()) {
    				++ans;
    				break;
    			}
    			else {
    				s.emplace(sum);
    				++i;
    			}
    		}
    		++i;
    	}
    	return ans;
    }
};