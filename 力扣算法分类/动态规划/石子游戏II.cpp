// https://leetcode.cn/problems/stone-game-ii/description/
// 构造基本的博弈过程，然后使用暴力的dp即可，复杂度比较高
// 关键在于dp状态的设计，常用的博弈状态为在某个状态下，一方比另外一方获得的优势



class Solution {
public:
    int stoneGameII(vector<int>& piles) {
    	int n = piles.size();

    	vector dp(n + 1, vector<int>(n + 1, INT_MIN));

    	for (int i = n; i >= 0; --i) {
    		for (int m = 1; m <= n; ++m) {
    			if (i == n) {
    				dp[i][m] = 0;
    			}
    			else {
    				int sum = 0;
    				for (int x = 1; x <= 2 * m; ++x) {
    					if (i + x > n) break;
    					sum += piles[i + x - 1];
    					dp[i][m] = max(dp[i][m], sum - dp[i + x][min(n, max(x, m))]);
    				}
    			}
    		}
    	}
    	return (dp[0][1] + accumulate(piles.begin(), piles.end(), 0)) / 2;
    }
};