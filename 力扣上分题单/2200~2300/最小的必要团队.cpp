// https://leetcode.cn/problems/smallest-sufficient-team/
// 01背包 + 子集枚举 + 位运算


class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
    	unordered_map<string, int> idx;

    	int n = people.size();
    	int cnt = 0;
    	for (string s : req_skills) idx[s] = cnt++;

    	vector<int> a(n);
    	for (int i = 0; i < n; ++i) {
    		for (string skill : people[i]) {
    			a[i] |= (1 << idx[skill]);
    		}
    	}

    	auto f = [&](long long v) -> int {
    		return __builtin_popcountll(v);
    	};

    	// 需要使用long long因为最多60个人
    	vector<long long> dp(1 << cnt, (1ll << n) - 1);
    	dp[0] = 0;
    	// 01背包
    	for (int i = 0; i < n; ++i) {
    		for (int j = (1 << cnt) - 1; j >= 0; --j) {
    			if ((j | a[i]) == j) {
    				// a[i] 是满足集合中的子集
    				// 但是这里需要注意的是并不是精确覆盖
    				// 枚举补集的非空子集
    				int t = j ^ a[i];
    				for (int s = a[i]; s > 0; s = (s - 1) & a[i]) {
    					if (f(dp[j]) > f(dp[s | t]) + 1)
    						dp[j] = dp[s | t] | (1ll << i);
    				}
    				// 空集
    				if (f(dp[j]) > f(dp[t]) + 1)
    					dp[j] = dp[t] | (1ll << i);
    			}
    		}
    	}
    	vector<int> b;
    	long long res = dp.back();
    	for (int i = 0; i < n; ++i)
    		if ((res >> i) & 1) b.emplace_back(i);
    	return b;
    }
};