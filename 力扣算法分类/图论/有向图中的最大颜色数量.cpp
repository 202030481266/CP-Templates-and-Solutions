// https://leetcode.cn/problems/largest-color-value-in-a-directed-graph/



class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
    	int n = colors.size(), m = edges.size();
    	vector<int> in(n);
    	vector<int> col(n);
    	vector<vector<int>> g(n);

    	for (auto e : edges) {
    		g[e[0]].emplace_back(e[1]);
    		++in[e[1]];
    	}
    	for (int i = 0; i < n; ++i) {
    		col[i] = colors[i] - 'a';
    	}
    	vector cnt(n, vector<int>(26));
    	queue<int> q;
    	int total = 0;
    	for (int i = 0; i < n; ++i) {
    		if (in[i] == 0) {
    			q.push(i);
    			cnt[i][col[i]] = 1;
    			++total;
    		}
    	}
    	while (!q.empty()) {
    		int u = q.front();
    		q.pop();
    		for (int v : g[u]) {
    			--in[v];
    			for (int i = 0; i < 26; ++i) {
    				cnt[v][i] = max(cnt[v][i], cnt[u][i]);
    			}
    			if (in[v] == 0) {
    				++cnt[v][col[v]];
    				++total;
    				q.push(v);
    			}
    		}
    	}
    	if (total != n) return -1;
    	int ans = 0;
    	for (int i = 0; i < n; ++i) {
    		for (int j = 0; j < 26; ++j) {
    			// 答案一定存在这里, 如果以i为终点的j不是该路径出现最多的，那么一定存在cnt[i][k] > cnt[i][j], ans = cnt[i][k]
    			ans = max(ans, cnt[i][j]);
    		}
    	}
    	return ans;
    }
};