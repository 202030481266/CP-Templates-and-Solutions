#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 200003;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 998244353;

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

ull ans, dp[64][64], f[64][64], pw[16];

int main() {
	int t;
	read(t);
	pw[1] = 2;
	for (int i = 2; i < 64; ++i) pw[i] = pw[i - 1] * 2;
	memset(dp, 0x3f, sizeof(dp));
	memset(f, 0x3f, sizeof(f));
	dp[0][0] = 0;
	f[0][0] = 0;
	for (int c = 1; c < 16; ++c) {
		for (int i = 63; i >= 0; --i) {
			for (int j = 63; j >= 0; --j) {
				if (i >= c) dp[i][j] = min(dp[i][j], dp[i - c][j] + pw[c]);
				if (j >= c) dp[i][j] = min(dp[i][j], dp[i][j - c] + pw[c]);
				if (i >= c) f[i][j] = min(f[i][j], f[i - c][j] + pw[c]);
				f[i][j] = min(f[i][j], min(f[max(0, i - c)][j], f[i][max(0, j - c)]) + pw[c]);
			}
		}
	}
	while (t--) {
		ull x, y;
		read(x); read(y);
		if (x < y) swap(x, y);
		uint hx = x ? 64 - __builtin_clzll(x) : 0, hy = y ? 64 - __builtin_clzll(y) : 0;
		if (y == 0) writeln(f[hx][0]);
		else {
			int a = hx - hy, b = 0, p = hy - 1;
			x >>= a;
			while (p >= 0 && ((x >> p) & 1) == ((y >> p) & 1)) --p; // [p, 0]
			ans = f[hx][hy];
			for (int i = hy; i >= p + 1; --i) ans = min(ans, dp[a + i][b + i]);
			writeln(ans);
		}
	}
}