// https://leetcode.cn/problems/di-string-match/
// 思维题目
// 贪心技巧：极限分配，每一次上升字段尽量分配大的数肯定就不会错，每一次下降的字段分配小的数同样道理



class Solution {
public:
    vector<int> diStringMatch(string s) {
    	int n = s.size();
    	vector<int> a(n + 1);

    	int maxx = n, minn = 0;
    	if (s[0] == 'D') a[0] = maxx--;
    	else a[0] = minn++;

    	for (int i = 0; i < n; ++i) {
			int j = i;
			while (j < n && s[j] == s[i]) ++j;
			if (s[i] == 'I') {
				for (int k = j; k >= i + 1; --k)
					a[k] = maxx--;
			}
			else {
				for (int k = j; k >= i + 1; --k)
					a[k] = minn++;
			}
			i = j - 1;
    	}
    	return a;
    }
};