// https://leetcode.cn/problems/minimum-time-to-finish-the-race/
// 线性动态规划+划定上界


class Solution {
	typedef long long ll;
public:
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
    	int n = tires.size();
    	vector<int> mn(18, 0x3f3f3f3f);
    	vector<int> f(changeTime + 1, 0x3f3f3f3f);
    	for (auto &c : tires) {
    		ll tim = c[0];
    		for (int i = 1, sum = 0; tim <= changeTime + c[0]; ++i) {
    			sum += tim;
    			mn[i] = min(mn[i], sum);
    			tim *= c[1];
    		}
    	}
    	f[0] = -changeTime;
    	for (int i = 1; i <= numLaps; ++i) {
    		for (int j = 1; j <= min(i, 17); ++j)
    			f[i] = min(f[i], f[i - j] + mn[j]);
    		f[i] += changeTime;
    	}
    	return f[numLaps];
    }
};