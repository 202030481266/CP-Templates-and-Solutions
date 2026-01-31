class Solution {
public:
    int maxGroupNumber(vector<int>& tiles) {
        int n = tiles.size();
        vector<vector<int>> dp(5, vector<int>(5, -1));
        dp[0][0] = 0;

        map<int, int> mp;
        for (int& p : tiles) ++mp[p];

        int pre_tile = 0;
        for (auto [tile, cnt] : mp) {
            if (tile - 1 != pre_tile) {
                // 那么之前的预留的牌都是无法使用的
                int init = dp[0][0];
                dp = vector<vector<int>>(5, vector<int>(5, -1));
                dp[0][0] = init;
            }
            vector<vector<int>> new_dp(5, vector<int>(5, -1));
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (dp[i][j] < 0) continue;
                    for (int shunzi = 0; shunzi <= min(cnt, min(i, j)); ++shunzi) {
                        int ni = j - shunzi; 
                        for (int k = 0; k <= min(4, cnt - shunzi); ++k) {
                            new_dp[ni][k] = max(new_dp[ni][k], dp[i][j] + shunzi + (cnt - shunzi - k) / 3);
                        }
                    }
                }
            }
            dp = move(new_dp);
            pre_tile = tile;
        }

        int ans = 0;
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                ans = max(ans, dp[i][j]);
        return ans;
    }
};