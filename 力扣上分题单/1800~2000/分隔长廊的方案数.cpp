// https://leetcode.cn/problems/number-of-ways-to-divide-a-long-corridor/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int numberOfWays(string corridor) {
    	int n = corridor.size();

    	vector<int> pos;
    	for (int i = 0; i < n; ++i) 
    		if (corridor[i] == 'S') pos.emplace_back(i);

    	if (pos.size() & 1 || pos.size() == 0) return 0;

    	long long ans = 1;
    	int m = pos.size();
    	for (int i = 0; i < m && i + 2 < m; i += 2) {
    		long long interval = pos[i + 2] - pos[i + 1];
    		ans = (ans * interval) % mod;
    	}
    	return ans;
    }
};