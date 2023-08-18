// https://leetcode.cn/problems/find-longest-awesome-substring/



class Solution {
public:
    int longestAwesome(string s) {
    	// 关键点：s 仅由数字组成，所以每一位字符只有10种可能
    	// 子字符串里面的所有的字符都是偶数个或者只有一个奇数个字符，那么使用前缀和判断的时候只需要判断奇偶性
    	int n = s.size(), pos[2000], ans = 0; 
    	memset(pos, -1, sizeof(pos));
    	int S = 0; // 记录奇偶状态
    	pos[0] = 0;
    	for (int i = 0; i < n; ++i) {
    		S ^= (1 << (s[i] - '0'));
    		// 如果为偶数长度
    		if (pos[S] != -1) ans = max(ans, i + 1 - pos[S]);
    		// 如果为奇数长度，枚举其中的数字
    		for (int j = 0; j < 10; ++j) {
    			int tmp = (S ^ (1 << j));
    			if (pos[tmp] != -1) ans = max(ans, i + 1 - pos[tmp]);
    		}
    		if (pos[S] == -1) pos[S] = i + 1;
    	}
    	return ans;
    }
};