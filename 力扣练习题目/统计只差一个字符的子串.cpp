// https://leetcode.cn/problems/count-substrings-that-differ-by-one-character/




class Solution {
public:
    int countSubstrings(string s, string t) {
    	if(s.size() < t.size()) swap(s, t);
    	int n = s.size(), m = t.size();

    	int ans = 0;
    	for (int len = 1; len <= m; ++len) {
    		for (int i = 0; i + len - 1 < m; ++i) {
    			for (int j = 0; j + len - 1 < n; ++j) {
    				// [i, i + len - 1] and [j, j + len - 1]
    				int p = i, q = j, cnt = 0;
    				while (p <= i + len - 1 && q <= j + len - 1) {
    					if (s[q++] != t[p++]) {
    						++cnt;
    						if (cnt > 1) break;
    					}
    				}
    				if (cnt == 1) ++ans;
    			}
    		}
    	}
    	return ans;
    }
};