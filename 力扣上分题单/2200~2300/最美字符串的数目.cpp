// https://leetcode.cn/problems/number-of-wonderful-substrings/



class Solution {
public:
    long long wonderfulSubstrings(string word) {
    	// 典型的奇偶性分类讨论问题
    	long long n = word.size(), f[2000], s = 0, ans = 0;
    	memset(f, 0, sizeof(f));
    	f[0] = 1;
    	for (int i = 0; i < n; ++i) {
    		s ^= (1 << (word[i] - 'a'));
    		ans += f[s];
    		for (int j = 0; j < 10; ++j) 
    			ans += f[s ^ (1 << j)];
    		++f[s];
    	}
    	return ans;
    }
};