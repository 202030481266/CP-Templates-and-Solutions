// https://leetcode.cn/problems/minimum-one-bit-operations-to-make-integers-zero/
// 数学+二进制


class Solution {
public:
    int minimumOneBitOperations(int n) {
    	// 答案的顺序就是格雷码所处的坐标
    	vector<int> a;
    	int x = n;
    	while (x) {
    		a.emplace_back(x % 2);
    		x /= 2;
    	}
    	reverse(a.begin(), a.end());
    	int ans = 0, flag = 1;
    	for (int i = 0, j = a.size(); i < a.size(); ++i, --j) {
    		if (flag) {
    			if (a[i] == 1) ans += pow(2, j - 1), flag = 0;
                else flag = 1;
    		}
    		else {
    			if (a[i] == 0) ans += pow(2, j - 1), flag = 0;
                else flag = 1;
    		}
    	}
    	return ans;
    }
};