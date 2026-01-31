// 技巧1：前后缀分解
// 技巧2：贪心匹配

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumScore(string s, string t) {
		int n = s.size();
		int m = t.size();
		int ans = 0;
		vector<int> suf(n + 1);
		// consider delete the substring
		suf[n] = m;
		for (int i = n - 1, j = m - 1; i >= 0; --i) {
			if (j >= 0 && s[i] == t[j])
				--j;
			suf[i] = j + 1;
		}
		ans = suf[0];
		for (int i = 0, j = 0; i < n && j < m; ++i) 
			if (s[i] == t[j] && suf[i + 1] >= ++j)
				ans = min(ans, suf[i + 1] - j);
		return ans;
    }
};
