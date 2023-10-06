// https://leetcode.cn/problems/broken-calculator/
// 逆向思维 + 分类讨论(贪心，按照奇偶或者数学形式来得到通过更少步骤得到相同的解)



class Solution {
public:
    int brokenCalc(int startValue, int target) {
    	int ans = 0;
    	int x = startValue, y = startValue;

    	while (y > x) {
    		if (y % 2) {
    			y >>= 1;
    		}
    		else ++y;
    		++ans;
    	}
    	return ans + (x - y);
    }
};