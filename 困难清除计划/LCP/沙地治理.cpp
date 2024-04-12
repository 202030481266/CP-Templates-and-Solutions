// 这道题单切秒了！！
// WA 4 次，终于是看出来了规律，研究到了 n = 9的情况！！

class Solution {
public:
    vector<vector<int>> sandyLandManagement(int n) {
    	// 1 2 3 1 循环构造即可
    	vector<vector<int>> ans;
    	int x = 0;
    	vector<int> a{1, 2, 3, 1};
    	for (int i = n; i >= 1; --i) {
    		int st = min(2 * i - 1, a[x]);
    		for (int j = st; j <= (x & 1 ? st : 2 * i - 1); j += 2)
    			ans.push_back({i, j});
    		x = (x + 1) % 4;
    	}
    	return ans;
    }
};