// https://leetcode.cn/problems/letter-tile-possibilities/



class Solution {
public:
    int numTilePossibilities(string tiles) {
    	int cnt[26], fac[8];
    	memset(cnt, 0, sizeof(cnt));
    	for (char ch : tiles) ++cnt[ch - 'A'];
    	vector<int> a;
    	for (int i = 0; i < 26; ++i) a.emplace_back(cnt[i]);
    	fac[0] = 1;
    	for (int i = 1; i <= 7; ++i) fac[i] = fac[i - 1] * i;
    	int ans = 0;
    	vector<int> tmp;
    	function<void(int)> dfs = [&](int d) {
    		if (d == a.size()) {
    			int sum = 0;
    			for (int c : tmp) sum += c;
    			sum = fac[sum];
    			for (int c : tmp) sum /= fac[c];
    			ans += sum;
    			return;
    		}
    		for (int i = 0; i <= a[d]; ++i) {
    			tmp.push_back(i);
    			dfs(d + 1);
    			tmp.pop_back();
    		}
    	};
    	dfs(0);
    	return ans - 1;
    }
};