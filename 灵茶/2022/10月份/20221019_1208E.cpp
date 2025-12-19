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

static constexpr int MAXN = 1000005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 998244353;


class FenwickSet {
private:
	int n, tot;       // n: 值域上限, tot: 当前元素总数
	vector<int> tr;   // 树状数组
	int high_bit;     // 倍增搜索的起始位 (2^k)

public:
	// 初始化：size 为值域大小 (例如 1000000)
	FenwickSet(int size) : n(size), tot(0) {
		tr.assign(n + 1, 0);
		// 计算足够覆盖 n 的最大 2 的幂，例如 n=10^6 时 high_bit = 1<<19 或 1<<20
		high_bit = 1;
		while ((high_bit << 1) <= n) high_bit <<= 1;
	}

	// 基础修改：val 处增加 delta
	void add(int val, int delta) {
		tot += delta;
		for (; val <= n; val += val & -val) tr[val] += delta;
	}

	// 基础查询：前缀和 [1, val]
	int ask(int val) {
		int res = 0;
		for (; val > 0; val -= val & -val) res += tr[val];
		return res;
	}

	// --- 高级接口 ---

	// 插入元素
	void insert(int val) {
		add(val, 1);
	}

	// 删除元素
	void erase(int val) {
		add(val, -1);
	}

	// 查找第 k 小 (树上倍增，O(log n))
	int kth(int k) {
		if (k > tot) return -1;
		int pos = 0;
		for (int i = high_bit; i > 0; i >>= 1) {
			if (pos + i <= n && tr[pos + i] < k) {
				pos += i;
				k -= tr[pos];
			}
		}
		return pos + 1;
	}

	// 获取最大值
	int get_max() {
		return tot == 0 ? -1 : kth(tot);
	}

	// 获取最小值
	int get_min() {
		return tot == 0 ? -1 : kth(1);
	}

	// 当前集合大小
	int size() { return tot; }
};

int n, m;
int arr[MAXN], rk[MAXN], num[MAXN];
ll ans[MAXN];
pii b[MAXN];

void upd_ans(int L, int R, int val) {
	// [L, R)
	ans[L] += val;
	ans[R] -= val;
}

void solve() {
	read(n); read(m);
	for (int r = 1, len; r <= n; ++r) {
		read(len);
		for (int i = 1; i <= len; ++i) {
			read(arr[i]);
			b[i].first = arr[i];
			b[i].second = i;
		}
		sort(b + 1, b + 1 + len);
		int cur_rank = 0;
		for (int i = 1; i <= len; ++i) {
			if (i == 1 || b[i].first != b[i - 1].first) {
				++cur_rank;
				num[cur_rank] = b[i].first;
			}
			rk[b[i].second] = cur_rank;
		}
		FenwickSet fen(cur_rank);
		int mx = 0, l = 1;
		for (int i = 1; i <= len; ++i) {
			fen.insert(rk[i]);
			while (l + m - len < i) fen.erase(rk[l++]);
			mx = fen.get_max();
			assert(mx != -1);
			// ans[i] += num[mx]
			if (i < m - len + 1) {
				if (num[mx] > 0) upd_ans(i, i + 1, num[mx]);
			}
			else upd_ans(i, i + 1, num[mx]);
		}
		// [len + 1, l + m - len + 1), from now on, every position can be zero
		if (len < m) {
			while (l + m - len < len + 1) fen.erase(rk[l++]);
			mx = fen.get_max();
			assert(mx != -1);
			if (num[mx] > 0) upd_ans(len + 1, m + l - len + 1, num[mx]);
			for (int i = m + l + 1 - len; i <= m; ++i) {
				fen.erase(rk[l++]);
				mx = fen.get_max();
				assert(mx != -1);
				if (num[mx] > 0) upd_ans(i, i + 1, num[mx]);
			}
		}
	}
	for (int i = 1; i <= m; ++i) {
		ans[i] += ans[i - 1];
		write(ans[i], ' ');
	}
}


int main() {
	int t = 1;
	// read(t);
	while (t--) solve();
}