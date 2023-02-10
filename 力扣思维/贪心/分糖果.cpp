// https://leetcode.cn/problems/distribute-candies/


class Solution {
public:
    int distributeCandies(vector<int>& candyType) {
    	int n = candyType.size();
    	unordered_map<int, bool> vis;

    	int ans = 0, cur = 0;
    	for (int i = 0; i < n && ans < (n / 2); ++i)
    		if (!vis[candyType[i]]) {
    			vis[candyType[i]] = true;
                ++ans;
    		}
    	return ans;
    }
};