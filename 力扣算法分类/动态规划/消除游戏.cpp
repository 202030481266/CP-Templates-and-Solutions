// https://leetcode.cn/problems/elimination-game/



class Solution {
public:
    int lastRemaining(int n) {
    	function<int(int,int)> dfs = [&](int v, int s) {
    		if (v == 1) return 1;
    		if (v == 2) {
    			if (s == 0) return 2;
    			else return 1;
    		} 
    		int k = (s ? v : 1);
            if (k & 1) return dfs(v / 2, s ^ 1) * 2;
            else return dfs(v / 2, s ^ 1) * 2 - 1;
    	};
    	return dfs(n, 0);
    }
};