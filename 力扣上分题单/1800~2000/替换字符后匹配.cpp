// https://leetcode.cn/problems/match-substring-after-replacement/



class Solution {
public:
    bool matchReplacement(string s, string sub, vector<vector<char>>& mappings) {
    	unordered_set<string> candi;
    	unordered_map<char,unordered_set<char>> mp;

    	for (auto c : mappings)
    		mp[c[0]].emplace(c[1]);

    	int m = sub.size();
    	int n = s.size();

    	if (m > n) return false;
    	for (int i = 0; i + m - 1 < n; ++i) 
    		candi.emplace(s.substr(i, m));

    	auto f = [&](string u) {
    		string t = sub;
    		for (int i = 0; i < m; ++i) {
    			if (u[i] == t[i]) continue;
    			if (mp.count(t[i]) == 0) return false;
    			if (mp[t[i]].count(u[i]) == 0) return false;
    		}
    		return true;
    	};

    	for (auto it = candi.begin(); it != candi.end(); ++it) {
    		if (f(*it)) return true;
    	}
    	return false;
    }
};