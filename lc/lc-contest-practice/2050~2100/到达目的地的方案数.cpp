// https://leetcode.cn/problems/number-of-ways-to-arrive-at-destination/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int countPaths(int n, vector<vector<int>>& roads) {
    	vector<long long> dis(n, 0x3f3f3f3f3f3f3f3f);
    	vector<long long> cnt(n);
    	vector<vector<pair<int, int>>> g(n);

    	for (auto c : roads) {
    		g[c[0]].emplace_back(make_pair(c[1], c[2]));
    		g[c[1]].emplace_back(make_pair(c[0], c[2]));
    	}

    	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    	dis[0] = 0;
			cnt[0] = 1;
    	q.emplace(dis[0], 0);
    	while (!q.empty()) {
    		auto [d, u] = q.top();
    		q.pop();
    		if (d != dis[u]) continue;
    		for (auto [v, w] : g[u]) {
    			if (dis[v] > dis[u] + w) {
    				dis[v] = dis[u] + w;
    				cnt[v] = cnt[u];
    				q.emplace(dis[v], v);
    			}
    			else if (dis[v] == dis[u] + w) {
    				cnt[v] = (cnt[v] + cnt[u]) % mod;
    			}
    		}
    	}
    	return cnt[n - 1];
    }
};