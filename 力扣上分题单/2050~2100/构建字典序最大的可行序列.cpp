// https://leetcode.cn/problems/construct-the-lexicographically-largest-valid-sequence/



class Solution {
public:
    vector<int> constructDistancedSequence(int n) {
    	bool find = false;
    	int N = 2 * n - 1;
    	vector<int> ans(N, 0);
        vector<int> res;
    	vector<bool> use(n + 1, false);

    	function<void(int)> dfs = [&](int pos) {
    		if (find) return;
    		if (pos == N) {
    			find = true;
                res = ans;
    			return;
    		}
    		if (ans[pos]) {
                dfs(pos + 1);
                return;  // details of return, if not will be a big mistake and hard to debug
            }
    		for (int i = n; i >= 1; --i) {
    			if (use[i]) continue;
    			if (i == 1) {
    				use[1] = true;
    				ans[pos] = 1;
    				dfs(pos + 1);
    				use[1] = false;
    				ans[pos] = 0;
    			}
    			else if (pos + i < N && ans[pos + i] == 0) {
    				use[i] = true;
    				ans[pos] = ans[pos + i] = i;
    				dfs(pos + 1);
    				use[i] = false;
    				ans[pos] = ans[pos + i] = 0;
    			}
    		}
    	};
    	dfs(0);
    	return res;
    }
};