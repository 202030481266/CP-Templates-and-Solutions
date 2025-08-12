#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 200005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

void solve() {
	uint n, k;
	cin >> n >> k;
	int a = bit_width(n), b = bit_width(k), diff = a - b;
	if ((n >> diff) >= k) ++diff;
	ull x = ((1u << diff) - 1) & n;
	cout << (1u + n) * x / 2 << '\n';
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve(); 
}

// ----------------------------------------------------------------------------------------
// fastio版本，因为这道题的时间在输入输出上， 108ms -> 62ms，提升非常大

#include <cstdio>
#include <cstdint>

// 极致优化的输入输出模板
namespace FastIO {
    constexpr int BUF_SIZE = 1 << 20;
    char in_buf[BUF_SIZE], out_buf[BUF_SIZE];
    char* in_ptr = in_buf + BUF_SIZE;
    char* out_ptr = out_buf;

    void flush_out() {
        fwrite(out_buf, 1, out_ptr - out_buf, stdout);
        out_ptr = out_buf;
    }

    void pc(char c) {
        if (out_ptr == out_buf + BUF_SIZE) flush_out();
        *out_ptr++ = c;
    }

    // getchar的缓冲区版本，比标准getchar快
    inline char gc() {
        if (in_ptr == in_buf + BUF_SIZE) {
            // 读完当前缓冲区后，从标准输入再读入一大块
            in_ptr = in_buf;
            int len = fread(in_buf, 1, BUF_SIZE, stdin);
            // 如果什么都没读到，就返回文件结束符
            if (len == 0) return EOF;
            in_buf[len] = '\0';
        }
        return *in_ptr++;
    }
    
    // 使用gc()的read函数模板
    template <typename T>
    void read(T& x) {
        x = 0;
        char c = gc();
        bool neg = false;
        while (c < '0' || c > '9') {
            if (c == '-') neg = true;
            c = gc();
        }
        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            c = gc();
        }
        if (neg) x = -x;
    }


    template <typename T>
    void write(T x) {
        if (x < 0) {
            pc('-');
            x = -x;
        }
        if (x == 0) {
            pc('0');
            return;
        }
        char stack[20]; 
        int top = 0;
        while (x > 0) {
            stack[top++] = x % 10 + '0';
            x /= 10;
        }
        while (top > 0) {
            pc(stack[--top]);
        }
    }
}

// __builtin_clz(0) 是未定义的，但题目保证 n, k >= 1
// 对于一个非零的32位无符号整数n, std::bit_width(n) 等价于 32 - __builtin_clz(n)
#if defined(__GNUC__) || defined(__clang__)
#define bit_width(x) (32 - __builtin_clz(x))
#else
#include <bit> // Fallback for other compilers
#define bit_width(x) std::bit_width(x)
#endif

int main() {
    struct Flusher {
        ~Flusher() { FastIO::flush_out(); }
    } flusher;

    int t;
    FastIO::read(t);
    while (t--) {
        uint32_t n, k;
        FastIO::read(n);
        FastIO::read(k);

        int a = bit_width(n);
        int b = bit_width(k);
        int diff = a - b;

        if ((n >> diff) >= k) {
            ++diff;
        }

        uint64_t x = ((1ULL << diff) - 1) & n;
        uint64_t result = (static_cast<uint64_t>(n) + 1) * x / 2;

        FastIO::write(result);
        FastIO::pc('\n');
    }

    return 0;
}