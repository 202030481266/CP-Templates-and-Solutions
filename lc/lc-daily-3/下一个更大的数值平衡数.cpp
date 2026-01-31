// xiaoshulin
// 2023.12.09
class Solution {
public:
    int nextBeautifulNumber(int n) {
		// many details
		vector<int> a{1, 22, 221, 333, 3331, 4444, 33322, 44441, 55555, 333221, 444422, 555551, 666666, 4444221};
		vector<vector<int>> mn{{0}, {1}, {22}, {122, 333}, {1333, 4444}, {14444, 33322, 55555}, {122333, 444422, 555551, 666666}, {1224444}};
		int i = upper_bound(a.begin(), a.end(), n) - a.begin();
		string s = to_string(n), ans, res = to_string(a[i]);
		vector<int> b(10);
		int x = a[i];
		while (x) {
			++b[x % 10];
			x /= 10;
		}
		if (res.size() > s.size()) {
			// get the smallest number
			for (int i = 0; i < 7; ++i)
				while (b[i]--) ans.push_back('0' + i);
			return stoi(ans);
		}
		int r = INT_MAX;
		function<void(int, int)> dfs = [&](int i, int flag) {
			if (i == s.size()) {
				if (stoi(ans) > n)
					r = min(r, stoi(ans));
				return;
			}
			int t = s[i] - '0';
			for (int j = (flag ? t : 1); j < 7; ++j) {
				if (b[j]) {
					--b[j];
					ans.push_back('0' + j);
					dfs(i + 1, j == t && flag);
					ans.pop_back();
					++b[j];
				}
			}
		};
		for (int v : mn[res.size()]) { 
			fill(b.begin(), b.end(), 0);
			while (v) {
				++b[v % 10];
				v /= 10;
			}
			dfs(0, 1);
		}
		return r;
    }
};
