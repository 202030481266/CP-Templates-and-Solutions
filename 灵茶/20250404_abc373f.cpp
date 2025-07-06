#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

static constexpr int maxn = 3003;

int N, W;
ll w[maxn], v[maxn];
ll dp[maxn][maxn];
pair<int, int> stk[maxn];
int ed, p;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> N >> W;
	for (int i = 1; i <= N; ++i) {
		cin >> w[i] >> v[i];
	}
	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < w[i]; ++j) {
			ed = 0;
			p = 0;
			for (int cap = j, num = 0; cap <= W; cap += w[i], ++num) {
				dp[i][cap] = dp[i - 1][cap];
				while (p < ed && stk[p].second <= num) p++;
				if (p) {
					int pre = stk[p - 1].first;
					dp[i][cap] = max(dp[i][cap], dp[i - 1][pre * w[i] + j] - pre * v[i] - pre * pre + 2 * pre * num + num * v[i] - num * num);
				}
				while (ed) {
					int pre = stk[ed - 1].first;
					ll v_cur = dp[i - 1][num * w[i] + j] - num * v[i] - num * num + 2 * num * stk[ed - 1].second;
					ll v_pre = dp[i - 1][pre * w[i] + j] - pre * v[i] - pre * pre + 2 * pre * stk[ed - 1].second;
					if (v_cur >= v_pre) --ed;
					else break;
				}
				if (!ed) {
					stk[ed++] = { num, 1 };
				}
				else {
					int pre = stk[ed - 1].first;
					ll delta_k = 2 * num - 2 * pre; 
					ll delta_b = (dp[i - 1][pre * w[i] + j] - pre * v[i] - pre * pre) - (dp[i - 1][num * w[i] + j] - num * v[i] - num * num);
					stk[ed++] = { num, (delta_b + delta_k - 1) / delta_k };
				}
			}
		}
	}
	cout << dp[N][W] << endl;
}