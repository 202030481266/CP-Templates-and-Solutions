// https://leetcode.cn/problems/delete-and-earn/



class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
    	int n = nums.size();
    	int mx = *max_element(nums.begin(), nums.end());

    	vector<int> cnt(mx + 1);
    	vector<pair<int, int>> b;
    	for (auto c : nums) ++cnt[c];
    	for (int i = 0; i <= mx; ++i)
    		if (cnt[i]) b.emplace_back(make_pair(i, cnt[i] * i));
    	int N = b.size();
    	vector dp(N, vector<int>(2, 0));
    	dp[0][0] = 0;
    	dp[0][1] = b[0].second;
    	for (int i = 1; i < N; ++i) {
    		dp[i][0] = max(dp[i - 1][1], dp[i - 1][0]);
    		if (b[i].first - 1 == b[i - 1].first) {
    			dp[i][1] = dp[i - 1][0] + b[i].second;
    		}
    		else dp[i][1] = dp[i][0] + b[i].second;
    	}
    	return max(dp[N - 1][0], dp[N - 1][1]);
    }
};