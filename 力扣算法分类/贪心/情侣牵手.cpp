// https://leetcode.cn/problems/couples-holding-hands/description/
// 最后的位置是固定的所以可以贪心分组交换（尺取法）


class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
    	unordered_map<int,int> pos;
    	for (int i = 0; i < row.size(); ++i)
    		pos[row[i]] = i;
    	int ans = 0;
    	for (int i = 0; i < row.size(); i += 2) {
    		int a = row[i], b = row[i + 1];
    		if ((a ^ 1) == b) continue;
    		int p = pos[a ^ 1];
    		pos[b] = p;
    		pos[row[p]] = i + 1;
    		swap(row[p], row[i + 1]);
    		++ans;
    	}
    	return ans;
    }
};