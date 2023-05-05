// https://leetcode.cn/problems/stone-game-ix/



class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
    	// alice 想要赢的话，就要努力让Bob无论怎么选都是3的倍数
    	// sum / 3 == 0 等价于 sum % 3 == 0
    	int cnt1 = 0, cnt2 = 0, cnt0 = 0, n = stones.size();
    	for (int &p : stones) {
    		p %= 3;
    		if (p == 1) ++cnt1;
    		else if (p == 2) ++cnt2;
    		else ++cnt0;
    	}
    	if ((cnt1 == 0 && cnt2 == 0) || n == 1) return false; // 没得选
    	// 因为 0牌是最无敌的，Bob一定是有0拿0，而Alice除了一开始，后面也是这样，因为反正自己不拿就会被别人拿
    	bool ans = false;
    	if (cnt0 & 1) { // Alice 先手
    		if (cnt1 > 0) ans = (ans || (cnt1 - 1 >= cnt2 + 2));
    		if (cnt2 > 0) ans = (ans || (cnt2 - 1 >= cnt1 + 2));
		}
		else {  // bob 先出手
			if (cnt1 > 0) ans = (ans || (cnt2 > cnt1 - 1));
			if (cnt2 > 0) ans = (ans || (cnt1 > cnt2 - 1));
		}
		return ans;
    }
};