// https://leetcode.cn/problems/minimum-operations-to-make-the-array-k-increasing/



class Solution {
public:
	int LIS(vector<int>& b) {
		vector<int> g(b.size(), INT_MAX);
		vector<int> f(b.size());
		int maxx = INT_MIN;
		for (int i = 0; i < b.size(); ++i) {
			int j = upper_bound(g.begin(), g.end(), b[i]) - g.begin();
			f[i] = j + 1;
			if (maxx < f[i])
				maxx = f[i];
			g[j] = b[i];
		}
		return maxx;
	}
    int kIncreasing(vector<int>& arr, int k) {
    	int n = arr.size();
    	vector<int> a[k];
    	for (int i = 0; i < k; ++i) {
    		for (int j = i; j < n; j += k)
    			a[i].emplace_back(arr[j]);
    	}
    	int ans = 0;
    	for (int i = 0; i < k; ++i)
    		ans += LIS(a[i]);
    	return ans;
    }
};