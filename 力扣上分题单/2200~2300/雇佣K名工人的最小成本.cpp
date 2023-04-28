// https://leetcode.cn/problems/minimum-cost-to-hire-k-workers/



class Solution {
	typedef pair<int, int> pii;
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
    	int n = quality.size(); 
    	vector<pii> a;
    	for (int i = 0; i < n; ++i) a.emplace_back(quality[i], wage[i]);
    	sort(a.begin(), a.end(), [&](const auto& x, const auto& y){
    		return x.second * y.first <= x.first * y.second;
    	});
    	long long sum = 0;
    	priority_queue<int> q;
    	for (int i = 0; i < k; ++i) q.emplace(a[i].first), sum += a[i].first;
    	double ans = sum * 1.0 * a[k - 1].second / a[k - 1].first;
    	for (int i = k; i < n; ++i) {
    		if (a[i].first < q.top()) {
    			sum -= q.top();
    			sum += a[i].first;
    			q.pop();
    			q.emplace(a[i].first);
    		}
    		ans = min(ans, sum * 1.0 * a[i].second / a[i].first);
    	}
    	return ans;
    }
};