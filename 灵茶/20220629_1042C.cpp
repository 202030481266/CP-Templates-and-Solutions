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

static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 998244353;


void solve() {
	int n;
	read(n);
	vector<int> arr(n);
	for (int& v : arr) read(v);
	int neg = 0, zero = 0, pos = 0;
	for (int v : arr) {
		if (v < 0) ++neg;
		if (v == 0) ++zero;
	}
	pos = n - neg - zero;
	auto output = [&](int ins, int x, int y = 0) -> void {
		if (ins == 2) {
			write(2, ' ');
			writeln(x + 1);
		}
		else {
			write(1, ' ');
			write(x + 1, ' ');
			writeln(y + 1);
		}
		};
	if (neg & 1) {
		int p = distance(arr.begin(), ranges::find_if(arr, [](int x) { return x < 0; })); // 使用最小的和0组合然后删除
		for (int i = p + 1; i < n; ++i) {
			if (arr[i] < 0 && arr[i] > arr[p]) p = i;
		}
		if (zero == 0) { // no zero
			int last = p > 0 ? 0 : 1;
			output(2, p);
			for (int i = 0; i < n; ++i) {
				if (i == p || i == last) continue;
				output(1, last, i);
				last = i;
			}
		}
		else { // have zero
			vector<int> b, c;
			for (int i = 0; i < n; ++i) {
				if (arr[i] == 0 || i == p) b.push_back(i);
				else c.push_back(i);
			}
			for (int i = 0; i < (int)b.size() - 1; ++i) output(1, b[i], b[i + 1]);
			if (b.size() < n) {
				output(2, b.back());
				for (int i = 0; i < (int)c.size() - 1; ++i) output(1, c[i], c[i + 1]);
			}
		}
	}
	else {
		vector<int> b, c;
		for (int i = 0; i < n; ++i) {
			if (arr[i] == 0) b.push_back(i);
			else c.push_back(i);
		}
		for (int i = 0; i < (int)b.size() - 1; ++i) output(1, b[i], b[i + 1]);
		if (b.size() < n) {
			if (b.size()) output(2, b.back()); // runtime error attention
			for (int i = 0; i < (int)c.size() - 1; ++i) output(1, c[i], c[i + 1]);
		}
	}
}

int main() {
	solve();
}
