// xiaoshulin
// 2024.1.4

class Solution {
	using ll = long long;
	using pii = pair<int, long long>;
public:
	vector<int> prefix_function(string& s) {
		vector<int> p(s.size());
		int k = 0; 
		for (int i = 1; i < s.size(); ++i) {
			while (k > 0 && s[k] != s[i]) k = p[k - 1];
			if (s[k] == s[i]) ++k;
			p[i] = k;
		}
		return p;
	}
	void find_substring(string& haystack, string& needle, vector<int>& res) {
        int m = needle.length();
        if (m == 0)
            return;
		vector<int> p = prefix_function(needle);
        for (int i = 0, k = 0; i < haystack.length(); i++) {
            while (k > 0 && needle[k] != haystack[i])
                k = p[k - 1];
            if (needle[k] == haystack[i])
                ++k;
            if (k == m) {
                k = p[k - 1]; 
				res.push_back(i);
			}
        }
    }
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
		int n = source.size();

		int N = original.size(), tot = 0;
		unordered_map<string, int> id;
		vector<string> from, to;
		for (int i = 0; i < N; ++i) {
			if (!id.count(original[i])) {
				id[original[i]] = tot++;
				from.push_back(original[i]);
			}
		}
		for (int i = 0; i < N; ++i) {
			if (!id.count(changed[i])) {
				id[changed[i]] = tot++;
				to.push_back(changed[i]);
			}
		}
		// build the graph
		const int inf = 0x3f3f3f3f;
		vector dis(tot, vector<int>(tot, inf));
		for (int i = 0; i < N; ++i) {
			int u = id[original[i]], v = id[changed[i]]; // u -> v
			dis[u][v] = min(dis[u][v], cost[i]);
		}
		// floyd, tot is mostly tot = 2 * N, every string is not the same
		for (int i = 0; i < tot; ++i) dis[i][i] = 0;
		for (int k = 0; k < tot; ++k) {
			for (int i = 0; i < tot; ++i) 
				for (int j = 0; j < tot; ++j)
					dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
		}
		// string match to accelerate
		// vector<vector<pii>> use(n);
		for (string& x : s) {
			vector<int> pos = find_substring(source, x);
			int len = x.size();
			for (int& p : pos) { 
				string y = target.substr(p - len + 1, len);
				if (id.count(y) && dis[id[x]][id[y]] < inf) {
					use[p].emplace_back(len, dis[id[x]][id[y]]);
				}
			}
		}
		vector<int> f(n, 0);
		for (int i = 0; i < n; ++i) { 
			if (source[i] == target[i]) {
				if (i == 0) f[0] = 1;
				else f[i] = f[i - 1] + 1;
			}
		}
		// dp
		const ll INF = 2e15;
		vector<ll> dp(n, INF);
		for (int i = 0; i < n; ++i) {
			for (int j = 1; j <= f[i]; ++j) {
				if (i - j >= 0) dp[i] = min(dp[i], dp[i - j]);
				else dp[i] = 0;
			}
			for (pii& p : use[i]) {
				int len = p.first;
                ll c = p.second;
				if (len <= f[i]) continue;
				if (i - len >= 0) dp[i] = min(dp[i], dp[i - len] + c);
				else dp[i] = min(dp[i], c);
			}
		}
		return dp[n - 1] == INF ? -1 : dp[n - 1];
    }
};
