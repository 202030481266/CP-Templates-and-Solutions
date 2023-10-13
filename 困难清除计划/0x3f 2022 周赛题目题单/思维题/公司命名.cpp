// https://leetcode.cn/problems/naming-a-company/



class Solution {
	unordered_map<string, unordered_set<char>> h;
	int cnt[30][30], total[30];
public:
    long long distinctNames(vector<string>& ideas) {
    	int n = ideas.size();
    	memset(cnt, 0, sizeof(cnt));
    	vector<string> sufix(n);
    	for (int i = 0; i < n; ++i) sufix[i] = ideas[i].substr(1);
    	for (int i = 0; i < n; ++i) h[sufix[i]].emplace(ideas[i][0]);
    	for (int i = 0; i < n; ++i) {
    		for (char ch : h[sufix[i]])
    			++cnt[ideas[i][0] - 'a'][ch - 'a'];
    		++total[ideas[i][0] - 'a'];
    	}
    	long long ans = 0;
    	for (int i = 0; i < n; ++i) {
    		for (char ch = 'a'; ch <= 'z'; ++ch) {
    			if (!h[sufix[i]].count(ch)) {
    				ans += (total[ch - 'a'] - cnt[ch - 'a'][ideas[i][0] - 'a']);
    			}
    		}
    	}
    	return ans;
    }
};