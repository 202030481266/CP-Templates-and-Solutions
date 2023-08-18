// https://leetcode.cn/problems/minimum-number-of-days-to-make-m-bouquets/



class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
    	int n = bloomDay.size();
    	int mx = *max_element(bloomDay.begin(), bloomDay.end());
    	if (1ll * m * k > 1ll * n) return -1;
    	vector<pair<int, int>> flower;

    	for (int i = 0; i < n; ++i)
    		flower.emplace_back(bloomDay[i], i);

    	sort(flower.begin(), flower.end());

    	auto f = [&](int day) {
    		vector<int> a(n);
    		int p = 0;
    		int cnt = 0;
    		while (p < n && flower[p].first <= day) a[flower[p++].second] = 1; 
    		p = 0;
    		while (p < n) {
    			int i = p;
    			while (i < n && a[i]) ++i;
    			cnt += (i - p) / k;
    			p = (i == p ? i + 1 : i);
    		}
    		return cnt >= m;
    	};

    	int l = 1, r = mx, ans;
    	while (l <= r) {
    		int mid = (l + r) >> 1;
    		if (f(mid))
    			ans = mid, r = mid - 1;
    		else l = mid + 1;
    	}
    	return ans;
    }
};