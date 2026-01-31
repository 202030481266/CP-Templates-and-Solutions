// https://leetcode.cn/problems/closest-room/
// 离线处理，排序技巧


class Solution {
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
    	int m = queries.size();
    	vector<vector<int>> qs;
    	vector<int> ans(m);

    	for (int i = 0; i < m; ++i) {
    		auto q = queries[i];
    		qs.emplace_back(vector<int>{q[0], q[1], i});
    	}
    	sort(qs.begin(), qs.end(), [](const vector<int>& x, const vector<int>& y){
    		// sort by the minisize
    		return x[1] > y[1];
    	});

    	sort(rooms.begin(), rooms.end(), [](const vector<int>& x, const vector<int>& y){
    		// sort by the minisize
    		return x[1] > y[1];
    	});
    	int p = 0;
    	set<int> s;
    	for (int i = 0; i < m; ++i) {
    		while (p < rooms.size() && rooms[p][1] >= qs[i][1]) s.emplace(rooms[p++][0]);
    		if (s.empty()) ans[qs[i][2]] = -1;
    		else {
    			auto it = s.lower_bound(qs[i][0]);
    			if (it == s.end()) {
    				ans[qs[i][2]] = *prev(it);
    			}
    			else if (it == s.begin()) {
    				ans[qs[i][2]] = *it;
    			}
    			else {
    				int left = qs[i][0] - *prev(it);
    				int right = *it - qs[i][0];
    				if (left <= right) ans[qs[i][2]] = *prev(it);
    				else ans[qs[i][2]] = *it;
    			}
    		}
    	}
    	return ans;
    }
};