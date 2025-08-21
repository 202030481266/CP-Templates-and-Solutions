#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100001;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1000000007;
static constexpr int dirs[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

namespace FastIO {
	const int BUFSIZE = 1 << 20; // 1MB缓冲区
	char ibuf[BUFSIZE], obuf[BUFSIZE];
	char* p1 = ibuf, * p2 = ibuf;
	char* p3 = obuf;

	// 读取单个字符
	inline char gc() {
		if (p1 == p2) {
			p1 = ibuf;
			p2 = ibuf + fread(ibuf, 1, BUFSIZE, stdin);
			if (p1 == p2) return EOF;
		}
		return *p1++;
	}

	// 输出单个字符
	inline void pc(char c) {
		if (p3 - obuf == BUFSIZE) {
			fwrite(obuf, 1, BUFSIZE, stdout);
			p3 = obuf;
		}
		*p3++ = c;
	}

	// 刷新输出缓冲区
	inline void flush() {
		fwrite(obuf, 1, p3 - obuf, stdout);
		p3 = obuf;
	}

	// 读取整数（支持负数）
	template<typename T>
	inline bool read(T& x) {
		x = 0;
		char c = gc();
		bool neg = false;

		// 跳过空白字符
		while (c != EOF && !isdigit(c) && c != '-') c = gc();
		if (c == EOF) return false;

		// 处理负号
		if (c == '-') {
			neg = true;
			c = gc();
		}

		// 读取数字
		while (isdigit(c)) {
			x = x * 10 + (c - '0');
			c = gc();
		}

		if (neg) x = -x;
		return true;
	}

	// 输出整数
	template<typename T>
	inline void write(T x) {
		static char stk[30];
		int top = 0;

		if (x < 0) {
			pc('-');
			x = -x;
		}

		if (x == 0) {
			pc('0');
			return;
		}

		while (x) {
			stk[top++] = '0' + (x % 10);
			x /= 10;
		}

		while (top) {
			pc(stk[--top]);
		}
	}

	// 输出整数并换行
	template<typename T>
	inline void writeln(T x) {
		write(x);
		pc('\n');
	}

	// 读取字符串（读到空白字符为止）
	inline bool read(string& s) {
		s.clear();
		char c = gc();

		// 跳过空白字符
		while (c != EOF && isspace(c)) c = gc();
		if (c == EOF) return false;

		// 读取非空白字符
		while (c != EOF && !isspace(c)) {
			s += c;
			c = gc();
		}
		return true;
	}

	// 读取整行
	inline bool getline(string& s) {
		s.clear();
		char c = gc();

		if (c == EOF) return false;

		while (c != EOF && c != '\n') {
			s += c;
			c = gc();
		}
		return true;
	}

	// 输出字符串
	inline void write(const string& s) {
		for (char c : s) pc(c);
	}

	// 输出字符串并换行
	inline void writeln(const string& s) {
		write(s);
		pc('\n');
	}

	// 读取单个非空白字符
	inline char readchar() {
		char c = gc();
		while (c != EOF && isspace(c)) c = gc();
		return c;
	}

	// 程序结束时自动刷新缓冲区
	struct AutoFlush {
		~AutoFlush() { flush(); }
	} auto_flush;
}
using namespace FastIO;

// 一种非常巧妙的贪心算法
// 递归过不了，太慢了
int n, cnt[maxn], dfn[maxn], ids[maxn], tot, father[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], ecnt;
int d1[maxn], d2[maxn], d = 0, len[maxn];

void addEdge(int u, int v) {
	to[++ecnt] = v;
	nxt[ecnt] = head[u];
	head[u] = ecnt;
}

void dfs(int u, int fa) {
	dfn[u] = ++tot;
	ids[tot] = u;
	father[u] = fa;
	for (int i = head[u]; i; i = nxt[i]) {
		if (to[i] != fa) {
			dfs(to[i], u);
			int t = d1[to[i]] + 1;
			if (t > d1[u]) d2[u] = d1[u], d1[u] = t;
			else if (t > d2[u]) d2[u] = t;
		}
	}
	d = max(d, d1[u] + d2[u]);
}

int query(int k) {
	int res = 0;
	for (int i = n, u, fa; i >= 1; --i) { // push写法比pull写法快了3倍，这里的细节就是，pull方法会遍历2遍的边
		u = ids[i];
		fa = father[u];
		if (d1[u] + d2[u] + 1 >= k) {
			++res;
			d1[u] = 0;
		}
		else d1[u]++;
		if (d1[u] > d1[fa]) {
			d2[fa] = d1[fa];
			d1[fa] = d1[u];
		}
		else if (d1[u] > d2[fa]) d2[fa] = d1[u];
	}
	for (int i = 1; i <= n; ++i) d1[i] = d2[i] = 0;
	return res;
}

int ans[maxn], memo[maxn];

int main() {
	read(n);
	for (int i = 1, u, v; i < n; ++i) {
		read(u); read(v);
		addEdge(u, v);
		addEdge(v, u);
	}
	dfs(1, 0);
	++d; // 节点数量
	int m = max(1, (int)sqrt(n * log2(n)));
	for (int i = 1; i <= m; ++i) ans[i] = query(i);
	int last = m + 1;
	ans[d] = query(d); // 直径
	for (int i = ans[m], l, r; i >= ans[d] && last <= n; i = query(last)) { // 剪枝
		l = last - 1, r = d + 1;
		while (l + 1 < r) {
			int mid = (l + r) / 2;
			if (memo[mid] == 0) memo[mid] = query(mid); // 缓存机制
			if (memo[mid] >= i) l = mid;
			else r = mid;
		}
		while (last <= l) ans[last++] = i;
	}
	for (int i = 1; i <= n; ++i) {
		writeln(ans[i]);
	}
}