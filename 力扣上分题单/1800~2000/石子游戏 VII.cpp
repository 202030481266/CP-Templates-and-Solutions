// https://leetcode.cn/problems/stone-game-vii/
// 记忆化搜索和常规的dp都会超时，非常离谱


class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
    	int n = stones.size();

    	vector dp(n + 1, vector(n + 1, vector<int>(2, -1)));
    	vector<int> sum(n + 1);
    	for (int i = 1; i <= n; ++i)
    		sum[i] = sum[i - 1] + stones[i - 1];

    	function<int(int, int, int)> dfs = [&](int l, int r, int p) -> int {
    		if (l >= r) return 0;
    		if (dp[l][r][p] != -1) return dp[l][r][p];
    		int ll = sum[r - 1] - sum[l - 1] - dfs(l, r - 1, p ^ 1);
    		int rr = sum[r] - sum[l] - dfs(l + 1, r, p ^ 1);
    		return dp[l][r][p] = max(ll, rr);
    	};
    	return dfs(1, n, 0);
    }
};



class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
    	int n = stones.size();

    	vector dp(n + 1, vector(n + 1, vector<int>(2, 0)));
    	vector<int> sum(n + 1);
    	for (int i = 1; i <= n; ++i)
    		sum[i] = sum[i - 1] + stones[i - 1];

    	for (int len = 2; i <= len; ++i) {
    		for (int i = 1; i + len - 1 <= n; ++i) {
    			int j = i + len - 1;
				dp[i][j][0] = max(sum[j - 1] - sum[i - 1] - dp[i][j - 1][1],
					sum[j] - sum[i] - dp[i + 1][j][1]);
				dp[i][j][1] = max(sum[j - 1] - sum[i - 1] - dp[i][j - 1][0],
					sum[j] - sum[i] - dp[i + 1][j][0]);
    		}
    	}
    	return dp[1][n][0];
    }
};



// 优化的dp，使用缓存优化并且降维
class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int len=stones.size();
        vector<vector<int>> secSum(len,vector<int>(len));
        for(int i=0;i<len;i++){
            for(int j=i;j<len;j++){
                if(i==j){
                    secSum[i][j]=stones[i];
                }
                else{
                    secSum[i][j]=secSum[i][j-1]+stones[j];
                }
            }
        }
        vector<vector<int>> dp(len,vector<int>(len,0));
        for(int i=len-1;i>=0;i--){
            for(int j=i+1;j<len;j++){
                dp[i][j]=max(secSum[i+1][j]-dp[i+1][j],secSum[i][j-1]-dp[i][j-1]);
            }
        }
        return dp[0][len-1];
    }
};
