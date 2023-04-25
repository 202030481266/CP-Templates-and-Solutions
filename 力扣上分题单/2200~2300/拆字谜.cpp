// https://leetcode.cn/problems/number-of-valid-words-for-each-puzzle/



class Solution {
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
    	// 4 <= words[i].length <= 50
    	// puzzles[i].length == 7  枚举子集的话，相当于 2^7 = 128, 128 * 10000 = 1.28e6，应该是正解
    	unordered_map<int, int> dp;
    	int n = words.size(), status = 0;
    	for (int i = 0; i < n; ++i) {
    		status = 0;
    		for (char ch : words[i]) status |= (1 << (ch - 'a'));
    		++dp[status];
    	}
    	vector<int> ans(puzzles.size());
    	int ss = 0, tmp = 0;
    	for (int i = 0; i < puzzles.size(); ++i) {
    		status = 0;
    		for (char ch : puzzles[i]) status |= (1 << (ch - 'a'));
    		ss = (1 << (puzzles[i][0] - 'a'));
    		tmp = (status ^ ss);
				ans[i] += dp[ss];
    		for (int sub = tmp; sub > 0; sub = (sub - 1) & tmp) 
    			ans[i] += dp[sub | ss];
    	}
    	return ans;
    }
};