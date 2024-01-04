// xiaoshulin
// 2024.1.4

class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
		swap(n, m); // n * m
		hFences.push_back(1);
		hFences.push_back(n);
		vFences.push_back(1);
		vFences.push_back(m);
		int h = hFences.size(), v = vFences.size();
		sort(hFences.begin(), hFences.end());
		sort(vFences.begin(), vFences.end());

		unordered_map<int, int> mp;
		for (int i = 0; i < v; ++i) {
			for (int j = i + 1; j < v; ++j) {
				mp[vFences[j] - vFences[i]] = 1;
			}
		}
		int ans = 0;
		const int mod = 1e9 + 7;
		for (int i = 0; i < h; ++i) {
			for (int j = i + 1; j < h; ++j) {
				if (mp.count(hFences[j] - hFences[i]))
					ans = max(ans, hFences[j] - hFences[i]);
			}
		}
		if (ans == 0) return -1;
		return 1ll * ans * ans % mod;
    }
};
