// xiaoshulin
// 2023.12.16

class Solution {
	using ll = long long;
public:
    int keyboard(int k, int n) {
		// I think this is a math problem

		const int mod = 1e9 + 7;

		int N = max(26, n); // [1, max(26, n)]
		vector<vector<ll>> C(N + 1, vector<ll>(27));
		for (int i = 0; i <= N; ++i)
			for (int j = 0; j <= min(i, 26); ++j) {
				if (j == 0) C[i][j] = 1;
				else C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
			}
		ll ans = 0;
		vector<int> num;
		function<void(int)> dfs = [&](int sum) {
			if (sum == n) {
				ll cnt = 1, tot = 1, s = n, last = 0, m = num.size();
				for (int& v : num) {
					cnt = (cnt * C[s][v]) % mod;
					s -= v;
				}
				for (int i = 1; i < num.size(); ++i) {
					// ascend
					if (num[i] != num[last]) {
						// [last, i)
						tot = tot  * C[m][i - last] % mod;
						m -= (i - last);
						last = i;
					}
				}
				// [last, n) , we can omit this one because m == n - last
				ans = (ans + cnt * C[26][num.size()] % mod * tot % mod) % mod;
			}
			if (sum > n) return;
			int rem = (26 - num.size()) * k;
			if (rem < n - sum) return;
			int st = (num.empty() ? 1 : num.back());
			for (int i = st; i <= k; ++i) {
				num.push_back(i);
				dfs(sum + i);
				num.pop_back();
			}
		};
		dfs(0);
		return ans;
    }
};
