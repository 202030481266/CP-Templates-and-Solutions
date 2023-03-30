// https://leetcode.cn/problems/odd-even-jump/



class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
    	int n = arr.size();

    	vector pos(n, vector<int>(2, -1));
    	set<pair<int, int>> s;
    	for (int i = 0; i < n; ++i) {
    		s.emplace(arr[i], i);
    	}
    	// the n-1 position is no need to jump
    	for (int i = 0; i < n - 1; ++i) {
    		s.erase(make_pair(arr[i], i));
    		auto it = s.lower_bound(make_pair(arr[i], 0));
    		if (it == s.end()) {
    			// all is smaller than arr[i]
    			int v = prev(it)->first;
    			// find the smallest position
    			auto fp = s.lower_bound(make_pair(v, 0));
    			pos[i][0] = fp->second;
    		}
    		else {
    			if (it->first == arr[i]) {
    				pos[i][0] = pos[i][1] = it->second;
    			}
    			else {
    				pos[i][1] = it->second;
    				if (it != s.begin()) {
    					// no smaller element
    					int v = prev(it)->first;
    					auto fp = s.lower_bound(make_pair(v, 0));
    					pos[i][0] = fp->second;
    				}
    			}
    		}
    	}

    	vector vis(n, vector<bool>(2, false));
    	vector dp(n, vector<bool>(2, false));

    	function<bool(int, int)> dfs = [&](int u, int flag) -> bool {
    		if (u == n - 1) return true;
    		if (vis[u][flag]) return dp[u][flag];
    		vis[u][flag] = true;

    		bool res = false;
    		if (pos[u][flag] != -1)
    			res = res || dfs(pos[u][flag], flag ^ 1);
    		return dp[u][flag] = res;
    	};
    	for (int i = 0; i < n - 1; ++i) {
    		if (!vis[i][1]) dfs(i, 1);
    	}
    	int ans = 0;
    	for (int i = 0; i < n - 1; ++i) {
    		if (dp[i][1]) ++ans;
    	}
    	return ans + 1;
    }
};