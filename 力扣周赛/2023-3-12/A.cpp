class Solution {
public:
    int vowelStrings(vector<string>& words, int left, int right) {
    	int n = words.size();
    	vector<int> sum(n + 1);

    	set<char> s{'a', 'e', 'i', 'o', 'u'};
    	for (int i = 1; i <= n; ++i) {
    		string t = words[i - 1];
    		sum[i] = sum[i - 1];
    		if (s.count(t[0]) && s.count(t.back()))
    			sum[i]++;
    	}
    	return sum[right + 1] - sum[left];
    }
};