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

static constexpr int maxn = 3002;
static constexpr int inf = 0x3f3f3f3f;

int n, m;
int pre[maxn][maxn], suf[maxn][maxn];
char grid[maxn][maxn];

int arr[maxn], b[maxn], idx[maxn], len = 0;

// 想不到一个 O(nm) 的做法，带一个 log(min(n, m)) 

int fenwick[maxn << 1], N;

inline int lowbit(int i) {
	return i & -i;
}

void update(int p, int val) {
	while (p <= N) {
		fenwick[p] += val;
		p += lowbit(p);
	}
}

int query(int p) {
	int res = 0;
	while (p) {
		res += fenwick[p];
		p -= lowbit(p);
	}
	return res;
}

int main() {
	read(n); read(m);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) grid[i][j] = readchar();
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (grid[i][j] == 'z') pre[i][j] = 1 + pre[i][j - 1];
		}
		for (int j = m; j >= 1; --j) {
			if (grid[i][j] == 'z') suf[i][j] = 1 + suf[i][j + 1];
		}
	}
	ll ans = 0;
	for (int sum = 2, i, j; sum <= n + m; ++sum) {
		i = min(n, sum - 1);
		j = sum - i;
		len = 0;
		while (i >= 1 && j <= m) {
			arr[++len] = pre[i][j];
			b[len] = suf[i][j];
			--i;
			++j;
		}
		i = 1;
		while (i <= len && arr[i] == 0) ++i;
		while (i <= len) {
			j = i + 1;
			while (j <= len && arr[j] > 0) ++j;
			// [i, j) is the interval we need to calculate, [i, j) -> [1, j - i]
			for (int k = i; k < j; ++k) {
				arr[k] -= (k - i + 1);
				idx[k] = k;
			}
			sort(idx + i, idx + j, [&](int x, int y) { return arr[x] > arr[y]; });
			int p = i, r;
			N = j - i;
			for (int k = i; k < j; ++k) {
				while (p < j && arr[idx[p]] >= i - k) {
					update(idx[p] - i + 1, 1);
					++p;
				}
				r = min(j - i, k - i + b[k]);
				int res = query(r) - query(k - i);
				ans += res; // [k - i + 1, r]
			}
			for (int k = 1; k <= N; ++k) fenwick[k] = 0;
			i = j;
		}
	}
	cout << ans << '\n';
}