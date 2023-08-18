// https://leetcode.cn/problems/minimum-interval-to-include-each-query/



class Solution {
	typedef pair<int, int> pii;
	typedef vector<int> vi;
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
    	int m = queries.size(), n = intervals.size();
    	set<pii> s;
    	vi ans(m, -1);
    	for (int i = 0; i < m; ++i) s.emplace(queries[i], i);
    	s.emplace(INT_MAX, INT_MAX); // 哨兵
    	// 排序答案
    	sort(intervals.begin(), intervals.end(), [&](const vi& a, const vi& b){
    		return (a[1] - a[0]) < (b[1] - b[0]);
    	});
    	for (int i = 0; i < n; ++i) {
    		int left = intervals[i][0], right = intervals[i][1];
    		for (auto it = s.lower_bound(pii{left, 0}); it->first <= right; it = s.erase(it))
    			ans[it->second] = (right - left + 1);
    	}
    	return ans;
    }
};