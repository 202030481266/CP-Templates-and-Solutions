// xiaoshulin
// 2023.12.08
class Solution {
	using pii = pair<int, int>;
public:
    int Leetcode(vector<string>& words) {
		int n = words.size();
		// hello leetcode
		// h : 1, e : 4, l : 3, o : 2, t : 1, c : 1, d : 1
		// we have a 11 of length binary number : e, l, o, h, t, c, d
		// atually there total 5 * 4 * 3 * 2 * 2 * 2 * 2 = 960 different status
		vector<int> offset(26), pos(26), tot(26), use;
		offset['d' - 'a'] = 0, pos['d' - 'a'] = 1, tot['d' - 'a'] = 1, use.push_back('d' - 'a');
		offset['c' - 'a'] = 1, pos['c' - 'a'] = 1, tot['c' - 'a'] = 1, use.push_back('c' - 'a');
		offset['t' - 'a'] = 2, pos['t' - 'a'] = 1, tot['t' - 'a'] = 1, use.push_back('t' - 'a');
		offset['h' - 'a'] = 3, pos['h' - 'a'] = 1, tot['h' - 'a'] = 1, use.push_back('h' - 'a');
		offset['o' - 'a'] = 4, pos['o' - 'a'] = 2, tot['o' - 'a'] = 2, use.push_back('o' - 'a');
		offset['l' - 'a'] = 6, pos['l' - 'a'] = 2, tot['l' - 'a'] = 3, use.push_back('l' - 'a');
		offset['e' - 'a'] = 8, pos['e' - 'a'] = 3, tot['e' - 'a'] = 4, use.push_back('e' - 'a');
		// calculate different status of each word
		int dp[1 << 8], count[26];
		// dp
		function<int(int,int)> dfs = [&](int u, int m) -> int {
			if (dp[u] != 0x3f3f3f3f) return dp[u];
			int cnt = 0, ones = __builtin_popcount(u);
			for (int i = 0; i < m; ++i) {
				if ((u >> i) & 1) {
					dp[u] = min(dp[u], dfs(u ^ (1 << i), m) + (i - cnt) * (m - ones - i + cnt));
					++cnt;
				}
			}
			return dp[u];
		};
		vector<pii> arr[n]; 
		for (int k = 0; k < n; ++k) {
			string s = words[k];
			int m = s.size(), N = 0;
			memset(dp, 0x3f, sizeof(dp));
			dp[0] = 0;
			for (int i = 0; i < m; ++i) {
				if (pos[s[i] - 'a']) N |= (1 << i);
			}
			dfs(N, m);
			for (int i = 1; i < (1 << m); ++i) {
				if (dp[i] != 0x3f3f3f3f) {
					int status = 0, valid = 1;
					memset(count, 0, sizeof(count));
					for (int j = 0; j < m; ++j) { 
						if ((i >> j) & 1) {
							++count[s[j] - 'a'];
							if (count[s[j] - 'a'] > tot[s[j] - 'a']) {
								valid = 0;
								break;
							}
						}
					}
					if (!valid) continue;
					for (int& idx : use)
						status |= (count[idx] << offset[idx]);
					arr[k].emplace_back(status, dp[i]);
				}
			}
		}

		// calculate all the words
		int f[1 << 11], valid[1 << 11];
		memset(f, 0x3f, sizeof(f));
		memset(valid, 0, sizeof(valid));
		for (int i = 0; i < (1 << 11); ++i) {
			int flag = 1;
			for (int& j : use) {
				int tmp = ((i >> offset[j]) & (1 << pos[j]) - 1);
				if (tmp > tot[j]) {
					flag = 0;
					break;
				}
			}
			valid[i] = flag;
		}
		f[0] = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = (1 << 11) - 1; j >= 0; --j) {
				if (valid[j]) {
					for (auto [status, cost] : arr[i]) {
						int tmp = 0, can_add = 1;
						for (int& idx : use) {
							int need = ((j >> offset[idx]) & (1 << pos[idx]) - 1);
							int cur = ((status >> offset[idx]) & (1 << pos[idx]) - 1);
							if (need < cur) {
								can_add = 0;
								break;
							}
							tmp |= ((need - cur) << offset[idx]);
						}
						if (can_add)
							f[j] = min(f[j], f[tmp] + cost);
					}
				}
			}
		}
		int end = 0;
		for (int& i : use) end |= (tot[i] << offset[i]);
		return f[end] == 0x3f3f3f3f ? -1 : f[end];
	}	
};
