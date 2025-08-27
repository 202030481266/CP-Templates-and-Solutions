#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100003;
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

int n, m, q;
int sr[maxn], sl[maxn], cnt[maxn], isbig[maxn];
ll tag[maxn], arr[maxn], sum[maxn];
ll b[maxn], N = 1;
int sz[maxn][250];
vector<int> bigblock;

// 这道题的分治不难想的
// 第一性原理：大集合一定不会遍历，否则复杂度一定不对，因此更新和计算都是依赖于tag
// 首先就很容易想到使用小集合暴力刷大集合，而且计算和维护特别简单，当时没有想到集合的交集可以这么容易算出来想了很多乱七八糟的方法

int main() {
	read(n); read(m); read(q);
	for (int i = 1; i <= n; ++i) read(arr[i]);
	for (int i = 1, k; i <= m; ++i) {
		read(k);
		sl[i] = N;
		while (k--) {
			read(b[N]);
			sum[i] += arr[b[N]];
			++N;
		}
		sr[i] = N;
	}
	int blen = sqrt(2 * (N - 1)); // [1, N)
	for (int i = 1; i <= m; ++i) {
		if (sr[i] - sl[i] >= blen) {
			bigblock.push_back(i);
			isbig[i] = 1;
		}
		sort(b + sl[i], b + sr[i]);
	}
	for (int i = 0; i < bigblock.size(); ++i) {
		for (int j = sl[bigblock[i]]; j < sr[bigblock[i]]; ++j) cnt[b[j]] = 1;
		for (int j = 1; j <= m; ++j) {
			for (int x = sl[j]; x < sr[j]; ++x) {
				if (cnt[b[x]]) ++sz[j][i];
			}
		}
		for (int j = sl[bigblock[i]]; j < sr[bigblock[i]]; ++j) cnt[b[j]] = 0;
	}
	char op;
	int k, x;
	ll ans = 0;
	while (q--) {
		op = readchar();
		if (op == '?') {
			read(k);
			ans = 0;
			if (!isbig[k]) {
				for (int i = sl[k]; i < sr[k]; ++i) ans += arr[b[i]];
			}
			else ans = sum[k];
			for (int i = 0; i < bigblock.size(); ++i)
				ans += sz[k][i] * tag[bigblock[i]];
			writeln(ans);
		}
		else {
			read(k); read(x);
			if (!isbig[k]) {
				for (int i = sl[k]; i < sr[k]; ++i) arr[b[i]] += x;
				for (int i = 0; i < bigblock.size(); ++i) sum[bigblock[i]] += 1ll * sz[k][i] * x;
			}
			else tag[k] += x;
		}
	}
}