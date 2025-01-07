// https://leetcode.cn/problems/maximize-win-from-two-segments/description/



class Solution {
public:
    int maximizeWin(vector<int>& pos, int k) {
    	int n = pos.size(), pre[n + 1]; 
    	int l = 0, ans = 0;
    	memset(pre, 0, sizeof(pre));
    	for (int i = 0; i < n; ++i) {
    		while (pos[i] - pos[l] > k) ++l;
    		ans = max(ans, i - l + 1 + pre[l]);
    		pre[i + 1] = max(pre[i], i - l + 1); 
    	}
    	return ans;
    }
};
