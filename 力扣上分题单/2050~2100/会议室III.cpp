// https://leetcode.cn/problems/meeting-rooms-iii/



class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
    	set<pair<long long, int>> use;
    	vector<int> cnt(n);

    	sort(meetings.begin(), meetings.end(), [](const vector<int>& x, const vector<int>& y){
    		return x[0] < y[0];
    	});

    	for (int i = 0; i < n; ++i) use.emplace(0, i);
    	for (int v = 0; v < meetings.size(); ++v) {
    		while (use.begin()->first < meetings[v][0]) {
    			int place = use.begin()->second;
    			use.erase(use.begin());
    			use.emplace(meetings[v][0], place);
    		}
    		int place = use.begin()->second;
    		long long time = use.begin()->first;
    		use.erase(use.begin());
    		++cnt[place];
    		use.emplace(time + meetings[v][1] - meetings[v][0], place);
    	}
    	int ans = 0, res = -1;
    	for (int i = 0; i < n; ++i) {
    		if (cnt[i] > ans) ans = cnt[i], res = i;
    	}
    	return res;
    }
};