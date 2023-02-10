// https://leetcode.cn/problems/maximum-length-of-pair-chain/
// 经典的贪心技巧，寻找最多的不重叠区间


class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
    	int n = pairs.size();

    	sort(pairs.begin(), pairs.end(), [&](const vector<int>& a, const vector<int>& b){
    		return (a[1] != b[1]) ? a[1] < b[1] : a[0] < b[0];
    	});
    	int ans = 1, cur = pairs[0][1];
    	for (int i = 1; i < n; ++i)
    		if (pairs[i][0] > cur) {
    			++ans;
    			cur = pairs[i][1];
    		}
    	return ans;
    }
};