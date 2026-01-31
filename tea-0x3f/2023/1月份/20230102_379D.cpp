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
typedef std::vector<vector<int>> vii;
typedef std::vector<ll> vl;
typedef std::vector<vector<ll>> vll;

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

	// 输出字符串（提前声明，供其他函数使用）
	inline void write(const string& s) {
		for (char c : s) pc(c);
	}

	// 输出C风格字符串
	inline void write(const char* s) {
		while (*s) pc(*s++);
	}

	// 读取整数（支持负数）
	template<typename T>
	inline typename enable_if<is_integral<T>::value, bool>::type read(T& x) {
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

	// 读取浮点数
	template<typename T>
	inline typename enable_if<is_floating_point<T>::value, bool>::type read(T& x) {
		x = 0;
		char c = gc();
		bool neg = false;

		// 跳过空白字符
		while (c != EOF && !isdigit(c) && c != '-' && c != '.') c = gc();
		if (c == EOF) return false;

		// 处理负号
		if (c == '-') {
			neg = true;
			c = gc();
		}

		// 读取整数部分
		while (isdigit(c)) {
			x = x * 10 + (c - '0');
			c = gc();
		}

		// 读取小数部分
		if (c == '.') {
			c = gc();
			T frac = 0.1;
			while (isdigit(c)) {
				x += (c - '0') * frac;
				frac *= 0.1;
				c = gc();
			}
		}

		// 处理科学计数法
		if (c == 'e' || c == 'E') {
			c = gc();
			int exp = 0;
			bool exp_neg = false;
			if (c == '-') {
				exp_neg = true;
				c = gc();
			}
			else if (c == '+') {
				c = gc();
			}
			while (isdigit(c)) {
				exp = exp * 10 + (c - '0');
				c = gc();
			}
			if (exp_neg) exp = -exp;
			x *= pow(10, exp);
		}

		if (neg) x = -x;
		return true;
	}

	// 输出整数
	template<typename T>
	inline typename enable_if<is_integral<T>::value>::type write(T x) {
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

	// 输出浮点数（默认6位小数）
	template<typename T>
	inline typename enable_if<is_floating_point<T>::value>::type write(T x, int precision = 6) {
		if (x < 0) {
			pc('-');
			x = -x;
		}

		// 处理特殊值
		if (isnan(x)) {
			write("nan");
			return;
		}
		if (isinf(x)) {
			write("inf");
			return;
		}

		// 四舍五入
		T round_val = 0.5;
		for (int i = 0; i < precision; i++) {
			round_val /= 10;
		}
		x += round_val;

		// 输出整数部分
		ll int_part = (ll)x;
		write(int_part);

		// 输出小数点和小数部分
		if (precision > 0) {
			pc('.');
			x -= int_part;
			for (int i = 0; i < precision; i++) {
				x *= 10;
				int digit = (int)x;
				pc('0' + digit);
				x -= digit;
			}
		}
	}

	// 输出整数并换行
	template<typename T>
	inline typename enable_if<is_integral<T>::value>::type writeln(T x) {
		write(x);
		pc('\n');
	}

	// 输出整数和分隔符
	template<typename T>
	inline typename enable_if<is_integral<T>::value>::type write(T x, char sep) {
		write(x);
		pc(sep);
	}

	// 输出浮点数并换行
	template<typename T>
	inline typename enable_if<is_floating_point<T>::value>::type writeln(T x, int precision = 6) {
		write(x, precision);
		pc('\n');
	}

	// 输出浮点数并且和分隔符
	template<typename T>
	inline typename enable_if<is_floating_point<T>::value>::type write(T x, char sep) {
		write(x);
		pc(sep);
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

static constexpr int MAXN = 100005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 1e9 + 7;


void solve() {
	int k, f, n, m;
	read(k); read(f); read(n); read(m);
	if (f == 0) {
		for (int i = 0; i < n; ++i) pc('A');
		pc('\n');
		for (int i = 0; i < m; ++i) pc('A');
		pc('\n');
		return;
	}
	// a-b, c-d, a-d, c-d, a-d, c-d,....
	//           b&c, d&a, d&c, d&a,....
	auto get = [](int n, char st, char ed) -> pii {
		if (n <= 2) {
			if (n == 2 && st == 'A' && ed == 'C') return { 1, 1 };
			return { 0, 0 };
		}
		if (st != 'A' && ed != 'C') return { 0, (n - 2) / 2 };
		return { 0, (n - 1) / 2 };
	};
	int c1 = -1, c2 = -1;
	auto cal = [&](char a, char b, char c, char d) -> void {
		auto [l1, r1] = get(n, a, b);
		auto [l2, r2] = get(m, c, d);
		for (int i = l1; i <= r1; ++i) {
			for (int j = l2; j <= r2; ++j) {
				ll x = i, y = j;
				int t = 3;
				for (; t <= k && y <= f; ++t) {
					ll add = 0;
					if (t == 3) {
						if (b == 'A' && c == 'C') ++add;
					}
					else {
						if (t % 2 == 0) {
							if (d == 'A' && a == 'C') ++add;
						}
						else {
							if (d == 'A' && c == 'C') ++add;
						}
					}
					ll nxt = x + y + add;
					x = y;
					y = nxt;
				}
				if (t > k && y == f) {
					c1 = i;
					c2 = j;
					return;
				}
			}
		}
	};
	auto build = [](int n, int cnt, char st, char ed) -> string {
		if (n == 1) return string(1, st);
		if (n == 2) {
			string s(1, st);
			s.push_back(ed);
			return s;
		}
		string res(n, 'X');
		if (st != 'A' && ed != 'C') {
			res[0] = st;
			res[n - 1] = ed;
			int i = 1;
			for (int j = 0; j < cnt; ++j, i += 2) {
				res[i] = 'A';
				res[i + 1] = 'C';
			}
			return res;
		}
		if (st == 'A') {
			int i = 0;
			for (int j = 0; j < cnt; i += 2, ++j) {
				res[i] = 'A';
				res[i + 1] = 'C';
			}
			if (i == 0) res[i] = st;
			res[n - 1] = ed;
		}
		else {
			int i = n - 1;
			for (int j = 0; j < cnt; i -= 2, ++j) {
				res[i] = 'C';
				res[i - 1] = 'A';
			}
			if (i == n - 1) res[i] = ed;
			res[0] = st;
		}
		return res;
	};
	auto search = [&](char a, char b, char c, char d) -> bool {
		cal(a, b, c, d);
		if (c1 != -1) {
			string s1 = build(n, c1, a, b);
			string s2 = build(m, c2, c, d);
			writeln(s1);
			writeln(s2);
			return true;
		}
		return false;
	};
	string T = "XAC";
	for (char a : T) {
		for (char b : T) {
			for (char c : T) {
				for (char d : T) {
					if (n == 1 && a != b) continue;
					if (m == 1 && c != d) continue;
					if (search(a, b, c, d)) return;
				}
			}
		}
	}
	writeln("Happy new year!");
}


int main() {
	int t = 1;
	//read(t);
	while (t--) solve();
}