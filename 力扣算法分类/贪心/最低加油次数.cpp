// https://leetcode.cn/problems/minimum-number-of-refueling-stops/
// 最少加油次数，那么在相同的情况下最好选择加油多的汽油站
// 也是经典的反悔贪心技巧

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
    	int n = stations.size();
    	int cur = startFuel, pos = 0;
    	priority_queue<int> q;

    	for (int i = 0; i < n; ++i) {
    		if (stations[i][0] > cur + pos) {
    			while (!q.empty() && cur + pos < stations[i][0]) {
    				cur += q.top();  // add fuel
    				q.pop();
    			}
    			if (cur + pos < stations[i][0]) return -1;
    		}
    		q.push(stations[i][1]);
    		cur -= (stations[i][0] - pos);
    		pos = stations[i][0];
    	}
    	while (!q.empty() && cur + pos < target) {
    		cur += q.top();
    		q.pop();
    	}
    	if (cur + pos < target) return -1;
    	return n - q.size();
    }
};