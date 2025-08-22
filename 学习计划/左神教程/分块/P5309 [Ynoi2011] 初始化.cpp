#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 200001;
static constexpr int maxb = 450;
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

// 卡常数，需要使用longlong进行加速，取模操作太慢了
int n, m;
int bl[maxb], br[maxb], belong[maxn];
ll pre[maxb][maxb], suf[maxb][maxb], sum[maxb], arr[maxn];

int main() {
	read(n); read(m);
	for (int i = 1; i <= n; ++i) read(arr[i]);
	int blen = sqrt(n), bnum = (n + blen - 1) / blen;
	for (int i = 1; i <= bnum; ++i) {
		bl[i] = (i - 1) * blen + 1;
		br[i] = min(n, i * blen);
		for (int j = bl[i]; j <= br[i]; ++j) {
			belong[j] = i;
			sum[i] += arr[j];
		}
	}
	int x, y, z, l, r, op;
	while (m--) {
		read(op);
		if (op == 1) {
			read(x); read(y); read(z);
			if (x > blen) {
				for (int i = y; i <= n; i += x) {
					arr[i] += z;
					sum[belong[i]] += z;
				}
			}
			else {
				// use T seperate into some group
				for (int i = y; i <= x; ++i) pre[x][i] += z;
				for (int i = y; i >= 1; --i) suf[x][i] += z;
			}
		}
		else {
			read(l); read(r);
			int lb = belong[l], rb = belong[r];
			ll ans = 0;
			if (rb - lb <= 1) {
				for (int i = l; i <= r; ++i) ans += arr[i];
			}
			else {
				for (int i = l; i <= br[lb]; ++i) ans += arr[i];
				for (int i = bl[rb]; i <= r; ++i) ans += arr[i];
				for (int i = lb + 1; i < rb; ++i) ans += sum[i];
			}
			--l;
			--r;
			for (int i = 1; i <= blen; ++i) {
				lb = l / i + 1;
				rb = r / i + 1;
				if (lb == rb) ans += pre[i][r % i + 1] - pre[i][l % i];
				else {
					ans += pre[i][i] * (rb - lb - 1) + suf[i][l % i + 1] + pre[i][r % i + 1];
				}
			}
			ans %= mod;
			writeln(ans);
		}
	}
}