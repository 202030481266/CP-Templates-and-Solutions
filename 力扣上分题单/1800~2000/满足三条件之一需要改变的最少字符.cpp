// https://leetcode.cn/problems/change-minimum-characters-to-satisfy-one-of-three-conditions/
// 两种解法，一就是DP，二就是枚举中间值


class Solution {
public:
    int minCharacters(string s1, string s2) {
    	// make b > a
    	auto f = [&](string a, string b) {
	    	vector<int> cnt1(30, 0), cnt2(30, 0);
	    	for (auto c : a) ++cnt1[c - 'a' + 1];
	    	for (auto c : b) ++cnt2[c - 'a' + 1];
	    	vector<int> sum(cnt2.begin(), cnt2.end());
	    	vector dp(30, vector<int>(2));
	    	for (int i = 3; i <= 26; ++i)
	    		sum[i] += sum[i - 1];
	    	set<char> s;
	    	vector<int> A;
	    	for (auto c : a) s.emplace(c);
	    	for (auto ch : s) 
	    		if (ch != 'a' && ch != 'z')
	    			A.emplace_back(ch - 'a' + 1);
            if (A.size() == 0) return cnt1[26] + cnt2[1];
	    	dp[A[0]][0] = sum[A[0]];
	    	dp[A[0]][1] = cnt1[A[0]];
	    	for (int i = 1; i < A.size(); ++i) {
	    		dp[A[i]][0] = sum[A[i]];
	    		dp[A[i]][1] = min(dp[A[i - 1]][1], dp[A[i - 1]][0]) + cnt1[A[i]];
	    	}
	    	return min(dp[A.back()][1], dp[A.back()][0]) + cnt1[26] + cnt2[1];
	    };
	    vector<int> cnt1(30, 0), cnt2(30, 0);
	    for (auto c : s1) ++cnt1[c - 'a'];
	    for (auto c : s2) ++cnt2[c - 'a'];
	    int ans = INT_MAX, total = s1.size() + s2.size();
		for (int i = 0; i < 26; ++i)
			ans = min(ans, total - cnt1[i] - cnt2[i]);
		return min(ans, min(f(s1, s2), f(s2, s1)));
    }
};