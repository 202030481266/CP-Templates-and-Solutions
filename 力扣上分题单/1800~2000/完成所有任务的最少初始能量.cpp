// https://leetcode.cn/problems/minimum-initial-energy-to-finish-tasks/



class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
    	int n = tasks.size();
    	int ans = 0, cur = 0;

    	sort(tasks.begin(), tasks.end(), [&](const vector<int>& a, const vector<int>& b){
    		return a[1] - a[0] > b[1] - b[0];
    	});

    	for (int i = 0; i < n; ++i) {
    		if (cur < tasks[i][1]) {
    			ans += (tasks[i][1] - cur);
    			cur = tasks[i][1];
    		}
    		if (cur < tasks[i][0]) {
    			ans += (tasks[i][0] - cur);
    			cur = tasks[i][0];
    		}
    		cur -= tasks[i][0];
    	}

    	return ans;
    }
};