// xiaoshulin
// 2023.12.09
class Solution {
public:
    int countCompleteSubstrings(string word, int k) {
		int n = word.size();

		// get the segments
		// enumerate the type of the window
		int ans = 0;
		int cnt[26];
		for (int t = 1; t <= 26; ++t) {
			memset(cnt, 0, sizeof(cnt));
			int l = 0, c = 0;
			for (int i = 0; i < n; ++i) {
				++cnt[word[i] - 'a'];
				if (cnt[word[i] - 'a'] == k) ++c;
				else if (cnt[word[i] - 'a'] == k + 1) --c;
				if (i > 0 && abs(word[i] - word[i - 1]) > 2) {
					// move l to i, [i, i]
					while (l < i) {
						--cnt[word[l] - 'a'];
						if (cnt[word[l] - 'a'] == k - 1) --c;
						else if (cnt[word[l] - 'a'] == k) ++c;
						++l;
					}
				}
				while (l < i - t * k + 1) {
					--cnt[word[l] - 'a'];
					if (cnt[word[l] - 'a'] == k - 1) --c;
					else if (cnt[word[l] - 'a'] == k) ++c;
					++l;
				}
				if (l == i - t * k + 1 && c == t) {
					++ans;
				}
			}
		}
		return ans;
    }
};
