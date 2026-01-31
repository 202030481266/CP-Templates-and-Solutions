// xiaoshulin
// 2024.1.18

class Solution {
	using ll = long long;
public:
    long long minimumRemoval(vector<int>& beans) {
		int n = beans.size();

		sort(beans.begin(), beans.end());
		vector<ll> sum(n + 1);
		for (int i = 0; i < n; ++i) {
			sum[i + 1] = sum[i] + beans[i];
		}
		ll ans = 1e10;
		for (int i = 1; i <= n; ++i) {
			// (i, n]
			ans = min(ans, sum[i - 1] + sum[n] - sum[i] - 1ll * (n - i) * beans[i - 1]);
		}
		return ans;
    }
};
