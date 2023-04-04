// https://leetcode.cn/problems/maximum-performance-of-a-team/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
    	vector<pair<int, int>> a(n + 1);

    	for (int i = 1; i <= n; ++i) {
    		a[i] = make_pair(speed[i - 1], efficiency[i - 1]);
    	}
    	sort(a.begin(), a.end(), [](const pair<int, int>& x, const pair<int, int>& y) {
    		return x.second < y.second;
    	});

    	// first calculate the top k elements
    	long long sum = 0;
    	long long ans = 0;
    	priority_queue<long long, vector<long long>, greater<long long>> q;
    	for (int i = n; i >= max(1, n - k + 1); --i) {
    		sum += a[i].first;
    		q.emplace(a[i].first);
    		ans = max(ans, sum * a[i].second);
    	}
    	if (k >= n) return ans;
    	for (int i = n - k; i >= 1; --i) {
    		if (a[i].first > q.top()) {
    			sum -= q.top();
    			q.pop();
    			q.emplace(a[i].first);
    			sum += a[i].first;
    		}
    		ans = max(ans, sum * a[i].second);
    	}
    	return ans % mod;
    }
};