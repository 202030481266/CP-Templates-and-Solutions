#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 200001;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1000000007;

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

int a[maxn], b[maxn];

int floor_div(int a, int b) {
	int q = a / b;
	int r = a % b;
	if (r != 0 && ((a ^ b) < 0)) {
		q -= 1;
	}
	return q;
}

int ceil_div(int a, int b) {
	int q = a / b;
	int r = a % b;
	if (r != 0 && ((a ^ b) > 0)) {
		q += 1;
	}
	return q;
}

int main() {
	int t, n;
	read(t);
	while (t--) {
		read(n);
		for (int i = 0; i < n; ++i) read(a[i]);
		for (int i = 0; i < n; ++i) read(b[i]);
		int x = 0, y = 0, w = 0, z = 0;
		for (int i = 0; i < n; ++i) {
			if (a[i] > b[i]) x += a[i];
			else if (a[i] < b[i]) y += b[i];
			else {
				if (a[i] < 0) ++w;
				if (a[i] > 0) ++z;
			}
		}
		int mx = max(x, y), mn = min(x, y), sum = x + y;
		sum -= w;
		if (mx - w >= mn) mx -= w;
		else {
			mn = floor_div(sum, 2);
			mx = sum - mn;
		}
		if (mn + z <= mx) writeln(mn + z);
		else writeln(floor_div(sum + z, 2));
	}
}