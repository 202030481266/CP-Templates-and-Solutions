#ifdef _MSC_VER
#include "pch.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char* x) { cerr << '\"' << x << '\"'; }
void __print(const string& x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template<typename T, typename V>
void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; }
template<typename T>
void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; }
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }

#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define debug(...)
#endif

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

static constexpr int maxn = 200001;
static constexpr int inf = 0x3f3f3f3f;

int n, a[maxn];
int head[maxn], to[maxn << 1], nxt[maxn << 1], ecnt;
int cnt[maxn][160], factor[maxn][80], len[maxn];
int dfn[maxn], ids[maxn], tot = 0, siz[maxn], f[maxn];
ll ans[maxn];
bool square[maxn];

void addEdge(int u, int v) {
	to[++ecnt] = v;
	nxt[ecnt] = head[u];
	head[u] = ecnt;
}

void dfs(int u, int fa) {
	dfn[u] = ++tot;
	ids[tot] = u;
	siz[u] = 1;
	f[u] = fa;
	for (int i = head[u]; i; i = nxt[i]) {
		if (to[i] != fa) {
			dfs(to[i], u);
			siz[u] += siz[to[i]];
		}
	}
}

int main() {
	read(n);
	int mx = 0;
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		if (a[i] > mx) mx = a[i];
	}
	for (int i = 0, u, v; i < n - 1; ++i) {
		read(u); read(v);
		addEdge(u, v);
		addEdge(v, u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j * j <= a[i]; ++j) {
			if (a[i] % j == 0) {
				factor[i][len[i]++] = j;
			}
		}
		square[i] = (factor[i][len[i] - 1] * factor[i][len[i] - 1] == a[i]);
	}
	for (int i = n; i >= 1; --i) { // enumerate the dfn
		int u = ids[i], fa = f[u], fd = dfn[fa];
		for (int j = 0; j < len[u]; ++j) {
			++cnt[i][j];
			++ans[factor[u][j]]; // itself
		}
		for (int j = (square[u] ? len[u] - 2 : len[u] - 1), k = len[u]; j >= 0; --j, ++k){ // re-calculate to save space
			int tmp = a[u] / factor[u][j];
			++cnt[i][k];
			++ans[tmp];
		}
		if (fa) { // the real hard thing!
			int x = 0, y = 0, nx, ny;
			int lenx = (square[u] ? len[u] * 2 - 1 : len[u] * 2);
			int leny = (square[fa] ? len[fa] * 2 - 1 : len[fa] * 2);
			while (x < lenx && y < leny) {
				nx = (x < len[u] ? factor[u][x] : a[u] / factor[u][lenx - x - 1]);
				ny = (y < len[fa] ? factor[fa][y] : a[fa] / factor[fa][leny - y - 1]);
				if (nx == ny) {
					ans[nx] += 1ll * cnt[i][x] * (1 + cnt[fd][y]);
					cnt[fd][y] += cnt[i][x];
					++x;
					++y;
				}
				else if (nx < ny) ++x;
				else ++y;
			}
		}
	}
	// erase duplicate contribution
	for (int i = mx; i >= 1; --i) {
		for (int j = i + i; j <= mx; j += i) {
			ans[i] -= ans[j];
		}
	}
	for (int i = 1; i <= mx; ++i) {
		if (ans[i]) {
			write(i);
			pc(' ');
			writeln(ans[i]);
		}
	}
}