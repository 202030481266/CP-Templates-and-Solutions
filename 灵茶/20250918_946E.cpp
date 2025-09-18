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

	// 输出浮点数并换行
	template<typename T>
	inline typename enable_if<is_floating_point<T>::value>::type writeln(T x, int precision = 6) {
		write(x, precision);
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

static constexpr int maxn = 200005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr int mod = 1e9 + 7;

int n;
int cnt[10], s[maxn], isodd[10];

void solve() {
	memset(cnt, 0, sizeof(cnt));
	memset(isodd, 0, sizeof(isodd));
	string num;
	read(num);
	int n = num.size();
	for (int i = 1; i <= n; ++i) {
		s[i] = num[i - 1] - '0';
		++cnt[s[i]];
	}
	int flag = 0;
	for (int i = 0; i <= 9; ++i) {
		if (cnt[i] & 1) {
			++flag;
			isodd[i] = 1;
		}
	}
	for (int i = n; i >= 1; --i) {
		--cnt[s[i]];
		if (cnt[s[i]] & 1) {
			++flag;
			isodd[s[i]] = 1; // even -> odd
		}
		else {
			--flag;
			isodd[s[i]] = 0; // odd -> even
		}
		int rem = n - i + 1;
		if (rem < flag - 1) continue;
		if (rem == flag - 1) {
			vector<int> tmp;
			for (int j = 0; j < 10; ++j) {
				if (isodd[j]) tmp.push_back(j);
			}
			sort(tmp.begin(), tmp.end());
			if (tmp[0] < s[i]) {
				int p = 0;
				while (p < tmp.size() && tmp[p] < s[i]) ++p;
				for (int j = 1; j < i; ++j) write(s[j]);
				write(tmp[p - 1]);
				for (int j = tmp.size() - 1; j >= 0; --j) {
					if (j == p - 1) continue;
					write(tmp[j]);
				}
				pc('\n');
				return;
			}
		}
		else {
			// rem > flag - 1, rem - 1 >= flag - 1 
			for (int j = s[i] - 1; j >= (i == 1 ? 1 : 0); --j) {
				if (isodd[j]) {
					for (int k = 1; k < i; ++k) write(s[k]);
					write(j);
					vector<int> tmp;
					for (int k = 0; k < 10; ++k) {
						if (isodd[k] && k != j) tmp.push_back(k);
					}
					sort(tmp.begin(), tmp.end());
					int r = rem - (int)tmp.size(); // (rem - 1) - (tmp.size() - 1)
					if (r & 1) {
						// we must use all the odds
						for (int k = 1; k < r; ++k) write(9);
						for (int k = tmp.size() - 1; k >= 0; --k) write(tmp[k]);
					}
					else {
						for (int k = 1; k <= r; ++k) write(9);
						for (int k = tmp.size() - 1; k >= 1; --k) write(tmp[k]);
					}
					pc('\n');
					return;
				}
				else {
					// 将会增加 odd 集合的数量
					if (rem - 1 >= flag) { // rem - 1 >= (flag + 1) - 1
						for (int k = 1; k < i; ++k) write(s[k]);
						write(j);
						vector<int> tmp{ j };
						for (int k = 0; k < 10; ++k) {
							if (isodd[k]) tmp.push_back(k);
						}
						sort(tmp.begin(), tmp.end());
						int r = rem - (int)tmp.size();
						if (r & 1) {
							for (int k = 1; k < r; ++k) write(9);
							for (int k = tmp.size() - 1; k >= 0; --k) write(tmp[k]);
						}
						else {
							for (int k = 1; k <= r; ++k) write(9);
							for (int k = tmp.size() - 1; k >= 1; --k) write(tmp[k]);
						}
						pc('\n');
						return;
					}
				}
			}
		}
	}
	// 不能同位
	for (int i = 1; i < n - 1; ++i) write(9);
	pc('\n');
}

int main() {
	int t;
	read(t);
	while (t--) solve();
}