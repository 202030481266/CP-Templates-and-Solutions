// https://leetcode.cn/problems/rabbits-in-forest/
// 贪心技巧： 不断抵消即可


class Solution {
public:
    int numRabbits(vector<int>& answers) {
    	int n = answers.size();
    	vector<int> cnt(1001);

    	for (auto c : answers) ++cnt[c];

    	int ans = 0;
    	for (int i = 0; i < 1001; ++i) {
    		if (!cnt[i]) continue;
    		int t = (cnt[i] / (i + 1));
    		if (cnt[i] % (i + 1))
    			ans += ((t + 1) * (i + 1));
    		else ans += (t * (i + 1));
    	}
    	return ans;
    }
};