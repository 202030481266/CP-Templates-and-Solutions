// https://leetcode.cn/problems/sum-of-scores-of-built-strings/description/
// 扩展KMP的模板题


class Solution {
public:
    long long sumScores(string s) {
    	int n = s.size(), nxt[n], p = 0, k = 1, l;
    	if (n == 1) return 1;
    	memset(nxt, 0, sizeof(nxt));
    	while (p + 1 < n && s[p] == s[p + 1]) ++p;
    	nxt[0] = n;
    	nxt[1] = p;
    	for (int i = 2; i < n; ++i) {
    		p = k + nxt[k] - 1;
    		l = nxt[i - k];
    		if (i + l <= p) nxt[i] = l;
    		else {
    			int j = max(0, p - i + 1);
    			while (i + j < n && s[i + j] == s[j]) ++j;
    			nxt[i] = j; // 必定刷新最大值
    			k = i;
    		}
    	}
    	long long ans = 0;
    	for (int i = 0; i < n; ++i) ans += (nxt[i]);
    	return ans;
    }
};