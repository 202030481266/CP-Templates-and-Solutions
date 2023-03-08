// https://leetcode.cn/problems/form-largest-integer-with-digits-that-add-up-to-target/
// 主要使用了背包模板的路径记录的方法


class Solution {
public:
    string largestNumber(vector<int>& cost, int target) {
    	int n = cost.size();
    	int mx = *max_element(cost.begin(), cost.end());

    	vector<int> num(mx + 1);
    	vector<vector<int>> b;
    	for (int i = 0; i < 9; ++i)
    		num[cost[i]] = i + 1;
    	for (int i = 0; i <= mx; ++i)
    		// {cost, value}
    		if (num[i]) b.emplace_back(vector<int>{i, num[i]});

    	sort(b.begin(), b.end(), [&](const vector<int>&a, const vector<int>&b){
    		return a[1] < b[1];
    	});

    	vector<int> dp(target + 1);
    	vector<int> path(target + 1);
    	for (int i = 0; i < b.size(); ++i)
    		for (int j = b[i][0]; j <= target; ++j) {
    			// 相同长度的情况下, 优先使用大的数字，并且必须存在
    			if ((dp[j - b[i][0]] > 0 || j == b[i][0]) && dp[j - b[i][0]] + 1 >= dp[j]) {
    				path[j] = j - b[i][0];
    				dp[j] = dp[j - b[i][0]] + 1;
    			}
    		}
    	int cur = target;
    	vector<int> use(10, 0);
    	if (dp[target] > 0) {
    		while (cur != 0) {
    			++use[num[cur - path[cur]]];
    			cur = path[cur];
    		}
    	}
    	string ans;
    	for (int i = 9; i >= 1; i--)
    		for (int j = 1; j <= use[i]; ++j)
    			ans += char('0' + i);
    	return ans.size() > 0 ? ans : "0";
    }
};