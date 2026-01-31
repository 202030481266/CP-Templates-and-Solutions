using namespace std;
using ll = long long;
using ui = unsigned int;
using node = tuple<double, int, int, int>;
static constexpr double inf = 1e9 + 7;

class Solution {
public:
	double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
		if (k == 1) {
			if (n > 1) return -1;
			return mul[0] * time[0];
		}
		ranges::sort(time);
		vector dp(1 << n, vector(2, vector<double>(m + 1, inf)));
		vector<int> mx(1 << n);
		for (int i = 1; i < (1 << n); ++i) {
			for (int j = 0; j < n; ++j) {
				if ((i >> j) & 1) {
					mx[i] = max(mx[i], time[j]);
				}
			}
		}
		// 使用贪心算出一个上界
		double ans = 0, cur = 0;
		int phase = 0;
		if (k >= n) {
			ans = mul[0] * time[n - 1];
		}
		else {
			int p = 1;
			while (p < n) {
				// 0 + [p, n)
				if (n - p + 1 <= k) {
					ans += mul[phase] * time[n - 1];
					break;
				}
				else {
					// [p, p + k - 1)
					double cost1 = mul[phase] * time[p + k - 2];
					phase = (phase + static_cast<int>(floor(cost1)) % m) % m;
					double cost2 = mul[phase] * time[0];
					phase = (phase + static_cast<int>(floor(cost2)) % m) % m;
					ans += cost1 + cost2;
					p += k - 1;
				}
			}
		}
		ui N = (1 << n) - 1;
		priority_queue<node, vector<node>, greater<node>> q;
		q.emplace(0, N, 1, 0);
        dp[N][1][0] = 0;
		while (!q.empty()) {
			auto [cost, S, go, phase] = q.top();
			q.pop();
			if (cost != dp[S][go][phase]) continue;
			if (S == 0) return cost;
			if (cost >= ans) return ans;
			if (go) {
				for (ui i = S; i; i = (i - 1) & S) {
					if (popcount(i) <= k) {
						double c = mx[i] * mul[phase];
						int step = static_cast<int>(floor(c)) % m, np = (phase + step) % m;
						if (dp[S ^ i][0][np] > c + cost) {
							dp[S ^ i][0][np] = c + cost;
							q.emplace(c + cost, S ^ i, 0, np);
						}
					}
				}
			}
			else {
				ui R = N ^ S;
				for (ui i = 0; i < n; ++i) {
					if ((R >> i) & 1) {
						double c = time[i] * mul[phase];
						int step = static_cast<int>(floor(c)) % m, np = (phase + step) % m;
						if (dp[S | (1 << i)][1][np] > c + cost) {
							dp[S | (1 << i)][1][np] = c + cost;
							q.emplace(c + cost, S | (1 << i), 1, np);
						}
					}
				}
			}
		}
		return -1;
	}
};