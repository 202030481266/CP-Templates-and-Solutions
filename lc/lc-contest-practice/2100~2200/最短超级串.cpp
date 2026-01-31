// https://leetcode.cn/problems/find-the-shortest-superstring/



class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
    	// words 中的所有字符串 互不相同，实际上相同的字符串没有任何意义
    	// 1 <= words.length <= 12，应该是爆搜
    	int n = words.size(), f[n][n], dp[n][1 << n], N = (1 << n) - 1; 
    	memset(f, 0, sizeof(f));
    	memset(dp, -1, sizeof(dp));
    	for (int i = 0; i < n; ++i)
    		for (int j = 0; j < n; ++j) 
    			for (int len = min(words[i].size(), words[j].size()); len >= 1; --len) {
    				bool flag = true; // words[i] + words[j]
    				int x = words[i].size() - len, y = 0;
    				while (x < words[i].size() && y < words[j].size()) {
    					if (words[i][x] == words[j][y]) ++x, ++y;
    					else { flag = false; break; }
    				}
    				if (flag) { f[i][j] = len; break; }
    			}
    	// 前面填的是第p个字符串在状态s下后面能够拼接的得到的对多重复字符数目
    	function<int(int, int)> dfs = [&](int p, int s) -> int {
    		if (s == 0) return 0;
    		int &res = dp[p][s];
    		if (res != -1) return dp[p][s];
    		res = 0;
    		for (int i = 0; i < n; ++i) 
    			if ((s >> i) & 1) {
    				int tmp = dfs(i, s ^ (1 << i));
    				if (f[p][i] + tmp > res) {
    					res = f[p][i] + tmp; 
	    			}
    			}
    		return res;
    	};
    	int mx = -1, st = -1;
    	for (int i = 0; i < n; ++i) {
    		int k = dfs(i, N ^ (1 << i));
    		if (k > mx) mx = k, st = i;
    	}
    	string ans = words[st];
    	function<void(int, int)> print = [&](int p, int s) {
    		if (s == 0) return;
    		int mx = INT_MIN, idx = -1;
    		for (int i = 0; i < n; ++i)
    			if ((s >> i) & 1) 
    				if (dp[i][s ^ (1 << i)] + f[p][i] > mx) {
    					mx = dp[i][s ^ (1 << i)] + f[p][i];
    					idx = i;
    				}
    		ans += words[idx].substr(f[p][idx], words[idx].size() - f[p][idx]);
			print(idx, s ^ (1 << idx));
    	};
    	print(st, N ^ (1 << st));
    	return ans;
    }
};