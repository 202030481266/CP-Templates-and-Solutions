// https://leetcode.cn/problems/minimum-jumps-to-reach-home/



class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
    	vector<int> in(20000);
    	vector dp(20000, vector<int>(2, -1));

    	for (auto c : forbidden) in[c] = 1;
		dp[x][0] = dp[x][1] = 0;
    	function<int(int, int)> dfs = [&](int p, int back) -> int {
    		int &res = dp[p][back];
    		if (res != -1) return res;
    		res = 0x3f3f3f3f;

    		// 往前跳
    		int pre = p - b, nxt = p + a;
    		if (nxt < 20000 && !in[nxt]) {
    			res = min(res, 1 + dfs(nxt, 1));
    		}
    		// 往后跳
    		if (back > 0 && pre >= 0 && !in[pre]) {
    			res = min(res, 1 + dfs(pre, 0));
    		}
    		return res;
    	};
    	return dfs(0, 1) == 0x3f3f3f3f ? -1 : dp[0][1];
    }
};