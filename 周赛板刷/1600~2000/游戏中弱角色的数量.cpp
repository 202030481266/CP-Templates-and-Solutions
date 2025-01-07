// https://leetcode.cn/problems/the-number-of-weak-characters-in-the-game/



class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& pro) {
    	// sort(pro.begin(), pro.end(), [&](const vector<int>& a, const vector<int>& b) {
    	// 	return (a[0] == b[0]) ? a[1] < b[1] : a[0] < b[0];
    	// });
    	unordered_map<int,int> mx;
    	vector<int> a;
    	vector<int> b;

    	for (auto c : pro) {
    		mx[c[0]] = max(mx[c[0]], c[1]);
    		a.emplace_back(c[0]);
    	}
    	sort(a.begin(), a.end());
    	a.erase(unique(a.begin(), a.end()), a.end());
    	int n = a.size();
    	b.resize(n);
    	b[n - 1] = mx[a[n - 1]];
    	for (int i = n - 2; i >= 0; --i)
    		b[i] = max(b[i + 1], mx[a[i]]);


    	int ans = 0;
    	for (auto c : pro) {
    		auto it = lower_bound(a.begin(), a.end(), c[0] + 1);
    		if (it == a.end()) continue;
    		int pos = it - a.begin();
    		if (b[pos] > c[1]) ++ans;
    	}

    	return ans;
    }
};