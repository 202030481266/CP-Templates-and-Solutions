using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

class Solution {
public:
	int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
		if (n == 1) return 0;
		vector g(n, vector<int>());
		for (auto& e : edges) {
			int u = e[0], v = e[1];
			g[u].push_back(v);
			g[v].push_back(u);
		}
		vector<int> arr(n, 1);
		vector<ll> val(n, 0);
		auto dfs = [&](auto&& self, int u, int fa, ll sum) -> void {
			sum += cost[u];
			if (g[u].size() == 1 && u != 0) {
				val[u] = sum;
				return;
			}
			ll pre = 0;
			for (int v : g[u]) {
				if (v != fa) {
					self(self, v, u, sum);
                    if (arr[u]) {
                        if (arr[v]) {
                            if (pre == 0) pre = val[v];
                            else if (pre != val[v]) arr[u] = 0;
                        }
                        else {
                            arr[u] = 0;
                        }
                    }
				}
			}
            if (arr[u]) val[u] = pre;
			};
        dfs(dfs, 0, -1, 0);
		if (arr[0]) return 0;
		vector<ll> groups;
		auto solve = [&](auto&& self, int u, int fa) -> void {
			if (arr[u]) {
				groups.push_back(val[u]);
				return;
			}
			for (int v : g[u]) {
				if (v != fa) {
					self(self, v, u);
				}
			}
			};
		solve(solve, 0, -1);
		int ans = 0;
		int mx = *ranges::max_element(groups);
		for (int v : groups) {
			if (v != mx) ++ans;
		}
		return ans;
	}
};