// https://leetcode.cn/problems/concatenated-words/



class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
    	unordered_set<string> s;
    	vector<string> ans;

    	for (auto c : words) s.emplace(c);
    	for (auto word : words) {
    		int n = word.size();
    		vector<bool> f(word.size() + 1);
    		f[0] = true;
    		s.erase(word);
    		for (int i = 1; i <= n; ++i) {
    			for (int j = 1; j <= i; ++j) {
    				string temp = word.substr(j - 1, i - j + 1);
    				f[i] = f[i] || (f[j - 1] && s.count(temp) > 0);
    			}
    		}
    		if (f[n]) ans.emplace_back(word);
    		s.emplace(word);
    	}
    	return ans;
    }
};