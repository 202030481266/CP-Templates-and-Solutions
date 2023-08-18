// https://leetcode.cn/problems/orderly-queue/



class Solution {
public:
    string orderlyQueue(string s, int k) {
    	string tmp = s;
    	sort(tmp.begin(), tmp.end());
    	if (k >= 2) return tmp;

    	// k == 1
    	int n = tmp.size();
    	tmp = s;
    	s = s + s;
    	for (int i = 0; i < n; ++i) {
    		string k = s.substr(i, n);
    		if (k < tmp) tmp = k;
    	}
    	return tmp;
    }
};