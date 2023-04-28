// https://leetcode.cn/problems/first-day-where-you-have-been-in-all-the-rooms/


class Solution {
public:
	static constexpr int mod = 1000000007;
    int firstDayBeenInAllRooms(vector<int>& nextVisit) {
    	// 关键点1：因为保证有解，所以不会出现状态闭环
    	// 关键点2：0 <= nextVisit[i] <= i，说明只会往回跳，想要到达i+1，就一定要先到达i
    	// 关键点3：回头走的路和一开始走的路的状态是一样的，因为都是走了偶数次，奇偶性不变，去一次回来又走一次，不变
    	int n = nextVisit.size(), f[n + 1][2];
    	memset(f, 0, sizeof(f));
    	f[1][1] = 1;
    	f[1][0] = 2;
    	for (int i = 2; i <= n; ++i) {
    		f[i][1] = (f[i - 1][0] + 1) % mod;
    		f[i][0] = (2 * f[i][1] % mod - f[nextVisit[i - 1] + 1][1] + 1 + mod) % mod;
    	}
    	return (f[n][1] - 1 + mod) % mod;
    }
};