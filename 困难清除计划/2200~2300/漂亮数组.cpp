// https://leetcode.cn/problems/beautiful-array/description/
// 奇偶构造


class Solution {
	unordered_map<int, vector<int>> mp;
public:
    vector<int> beautifulArray(int n) {
    	if (mp.find(n) != mp.end()) return mp[n];
    	vector<int> tmp(n);
    	if (n == 1) tmp[0] = 1;
    	else {
    		int k = 0;
    		for (int x : beautifulArray((n + 1) / 2)) tmp[k++] = 2 * x - 1;
    		for (int x : beautifulArray(n / 2)) tmp[k++] = 2 * x;
    	}
    	mp[n] = tmp;
    	return tmp;
    }
};