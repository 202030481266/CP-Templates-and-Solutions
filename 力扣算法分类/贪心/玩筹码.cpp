// https://leetcode.cn/problems/minimum-cost-to-move-chips-to-the-same-position/
// 朴素的规律发现



class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
    	int n = position.size();
    	int odd = 0;

    	// remove to even, and the cost is always odd
    	// remove to odd, and the cost is always even
    	for (auto c : position) 
    		if (c & 1) ++odd;
    	return min(odd, n - odd);
    }
};