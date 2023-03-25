// https://leetcode.cn/problems/find-the-longest-substring-containing-vowels-in-even-counts/
// 一个非常优秀的想法就是使用哈希表来进行存储字母出现的奇偶性，非常巧妙


class Solution {
public:
    int findTheLongestSubstring(string s) {
    	int n = s.size();
    	int cur = 0, ans = 0;

    	vector<int> hs(32, -1);  // 存储奇偶性
    	hs[0] = 0;

    	for (int i = 0; i < n; ++i) {
    		if (s[i] == 'a') {
    			cur ^= (1 << 0);
    		}
    		else if (s[i] == 'e') {
    			cur ^= (1 << 1);
    		}
    		else if (s[i] == 'i') {
    			cur ^= (1 << 2);
    		}
    		else if (s[i] == 'o') {
    			cur ^= (1 << 3);
    		}
    		else if (s[i] == 'u') {
    			cur ^= (1 << 4);
    		}
    		if (hs[cur] >= 0) {
    			ans = max(ans, i + 1 - hs[cur]);
    		}
    		else {
    			hs[cur] = i + 1;
    		}
    	}
    	return ans;
    }
};