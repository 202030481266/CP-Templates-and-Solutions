// https://leetcode.cn/problems/minimum-money-required-before-transactions/
// 任意顺序都能完成
// 那么我们只关心其中的减少钱的项目


class Solution {
public:
    long long minimumMoney(vector<vector<int>>& transactions) {
    	int n = transactions.size();

    	vector<int> tmp;
    	long long sum = 0, res = 0;
    	for (int i = 0; i < n; ++i) {
    		if (transactions[i][0] > transactions[i][1]) {
    			tmp.emplace_back(i);
    			sum += (transactions[i][0] - transactions[i][1]);
    		}
			else res = max(res, 1ll * transactions[i][0]);
    	}
    	long long ans = 0;
    	for (int i = 0; i < tmp.size(); ++i) {
    		ans = max(ans, sum + transactions[tmp[i]][1]);
    	}
    	return max(ans, res + sum);
    }
};