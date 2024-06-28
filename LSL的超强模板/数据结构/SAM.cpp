/*
	Created by xiaoshulin
	2023-5-27
	Space cost: O(n|C|)
	time cost: O(nlog|C|)
*/
#define maxn 1000010

struct Suffix_Automaton {
	int len[maxn << 1], link[maxn << 1];
	int ch[maxn << 1][26];   // 注意默认使用英文字母，字符集如果复杂的话需要使用 map<char, int>
	int f[maxn << 1][26];
	int siz, last;
	vector<vector<int>> g;

	void init() {
		memset(len, 0, sizeof(len));
		memset(link, 0, sizeof(link));
		memset(ch, 0, sizeof(ch));
		memset(f, 0, sizeof(f));
		siz = last = 0;
		g.assign(maxn * 2, vector<int>{});
		link[0] = -1; // 祖先节点
	}
	void extend(const char* str) {
		int n = strlen(str);
		for (int pos = 0; pos < n; ++pos) {
			int cur = ++siz, p = last, c = str[pos] - 'a';
			len[cur] = len[p] + 1;
			f[cur] = 1; // 大小加一
			while (p != -1 && !ch[p][c]) {
				ch[p][c] = cur;
				p = link[p];
			}
			if (p == -1) link[cur] = 0;
			else {
				int q = ch[p][c];
				if (len[q] == len[p] + 1) link[cur] = q;
				else {
					int copy = ++siz;
					len[copy] = len[p] + 1;
					link[copy] = link[q];
					for (int i = 0; i < 26; ++i)
						ch[copy][i] = ch[q][i];
					while (p != -1 && ch[p][c] == q) {
						ch[p][c] = copy;
						p = link[p];
					}
					link[q] = link[cur] = copy;
				}
			}
			last = cur;
		}
		for (int i = 1; i <= siz; ++i) g[link[i]].push_back(i); // 建立后缀树
	}
	void dfs(int u) {  
		for (int v : g[u]) {
			dfs(v);
			f[u] += f[v];
		}
	}
};


// map 版本，同时把所有的字符映射称为一个整数
int siz, last, n;
int a[maxn];
struct Suffix_Automaton {
	int len, link;
	map<int, int> ch;
} sam[maxn << 1];

void extend() {
	sam[0].link = -1;
	for (int i = 0; i < n; ++i) {
		int cur = ++siz, p = last;
		sam[cur].len = sam[p].len + 1;
		while (p != -1 && !sam[p].ch.count(a[i])) {
			sam[p].ch[a[i]] = cur;
			p = sam[p].link;
		}
		if (p == -1) sam[cur].link = 0;
		else {
			int q = sam[p].ch[a[i]];
			if (sam[q].len == sam[p].len + 1) {
				sam[cur].link = q;
			}
			else {
				int copy = ++siz;
				sam[copy].len = sam[p].len + 1;
				sam[copy].link = sam[q].link;
				sam[copy].ch = sam[q].ch;
				while (p != -1 && sam[p].ch.count(a[i]) && sam[p].ch[a[i]] == q) {
					sam[p].ch[a[i]] = copy;
					p = sam[p].link;
				}
				sam[cur].link = sam[q].link = copy;
			}
		}
		last = cur;
	}
}



