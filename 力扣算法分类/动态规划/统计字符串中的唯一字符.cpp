// https://leetcode.cn/problems/count-unique-characters-of-all-substrings-of-a-given-string/



class Solution {
public:
    int uniqueLetterString(string s) {
    	int n = s.size();

    	vector<int> p[26];

    	for (int i = 0; i < n; ++i) {
    		p[s[i] - 'A'].emplace_back(i);
    	}
    	vector<int> c(26);
    	int ans = 0;
    	for (int i = 0; i < n; ++i) {
    		int cur = s[i] - 'A';
    		int pos = p[cur][c[cur]];
    		int left = (c[cur] == 0) ? pos : pos - p[cur][c[cur] - 1] - 1;
    		int right = (c[cur] == p[cur].size() - 1) ? n - pos - 1 : p[cur][c[cur] + 1] - 1 - pos; 
    		ans += (left + 1) * (right + 1);
    		++c[cur];
    	}
    	return ans;
    }
};