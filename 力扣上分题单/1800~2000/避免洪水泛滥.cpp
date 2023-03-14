// https://leetcode.cn/problems/avoid-flood-in-the-city/



class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
    	int n = rains.size();
    	unordered_map<int, int> status;
    	set<int> chance;
    	vector<int> ans(n);

    	for (int i = 0; i < n; ++i) {
    		if (rains[i] > 0) {
    			ans[i] = -1;
    			if (status[rains[i]]) {
    				// find chance
    				auto it = chance.lower_bound(status[rains[i]]);
    				if (it == chance.end()) return vector<int>{};
    				ans[*it - 1] = rains[i];
    				chance.erase(it);
    			}
    			status[rains[i]] = i + 1;
    		}
    		else {
    			chance.emplace(i + 1);
    		}
    	} 
    	for (auto &c : ans)
    		if (!c) c = 1;
    	return ans;
    }
};