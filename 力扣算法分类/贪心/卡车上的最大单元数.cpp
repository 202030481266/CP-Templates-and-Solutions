// https://leetcode.cn/problems/maximum-units-on-a-truck/
// 非常简单的贪心技巧，既然最后的箱子数量是有限制的，那么就选择那些大箱子



class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
    	priority_queue<pair<int,int>> q;

    	for (auto c : boxTypes)
    		q.emplace(c[1], c[0]);

    	int ans = 0;
    	while (!q.empty() && truckSize) {
    		auto cur = q.top();
    		q.pop();
    		if (truckSize >= cur.second)
    			ans += cur.first * cur.second, truckSize -= cur.second;
    		else {
    			ans += truckSize * cur.first;
    			break;
    		}
    	}
    	return ans;
    }
};