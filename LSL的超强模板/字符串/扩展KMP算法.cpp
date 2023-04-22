// 扩展KMP算法

struct Z {
	string s;
	vector<int> nxt;
	Z() {}
	Z(string _s): s(_s), nxt(s.size()) {}
	// 获取next数组
	void qnxt() {
		int len = s.length(), p = 0, k = 1, l;
		nxt[0] = len;
		while (p + 1 < len && s[p] == s[p + 1]) ++p;
		nxt[1] = p;  //暴力匹配获得nxt[1]的值
		for (int i = 2; i < len; ++i) {
			p = k + nxt[k] - 1;
			l = nxt[i - k];
			if (i + l <= p) nxt[i] = l;
			else {
				int j = max(0, p - i + 1);
				while (i + j < len && s[i + j] == s[j]) ++j;
				nxt[i] = j; // 此时一定刷新了最大值
				k = i;
			}
		}
	}
	// 获取extend数组，计算t字符串对于s的next数组，计算思路和上面是一样的
	vector<int> exkmp(string t) {
		int lt = t.length(), ls = s.length(), p = 0, k = 0, l;
		vector<int> ext(lt);
		while (p < lt && p < ls && s[p] == t[p]) ++p;
		ext[0] = p;
		for (int i = 1; i < lt; ++i) {
			p = k + ext[k] - 1;
			l = nxt[i - k];
			if (i + l <= p) ext[i] = l;
			else {
				int j = max(0, p - i + 1);
				while (j < ls && i + j < lt && t[i + j] == s[j]) ++j;
				ext[i] = j;
				k = i;
			}
		}
		return ext;
	}
};
