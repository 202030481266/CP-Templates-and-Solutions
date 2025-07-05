// 傻逼超级卡常数题目

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

static constexpr int maxn = 2000005;

//-------------------fastIO----------------------
#define fcin OY::IO::InputHelper::get_instance()
#define fcout OY::IO::OutputHelper::get_instance()
#define endl '\n'
#ifndef INPUT_FILE
#define INPUT_FILE "in.txt"
#endif
#ifndef OUTPUT_FILE
#define OUTPUT_FILE "out.txt"
#endif
namespace OY {
    namespace IO {
        using size_type = size_t;
        static constexpr size_type INPUT_BUFFER_SIZE = 1 << 16, OUTPUT_BUFFER_SIZE = 1 << 16, MAX_INTEGER_SIZE = 20, MAX_FLOAT_SIZE = 50;
#ifdef OY_LOCAL
        static constexpr char input_file[] = INPUT_FILE, output_file[] = OUTPUT_FILE;
#else
        static constexpr char input_file[] = "", output_file[] = "";
#endif
        struct InputHelper {
            FILE *m_file_ptr;
            char m_buf[INPUT_BUFFER_SIZE], *m_end, *m_cursor;
            bool m_ok;
            InputHelper &set_bad() { return m_ok = false, *this; }
            template <size_type BlockSize>
            void _reserve() {
                size_type a = m_end - m_cursor;
                if (a >= BlockSize) return;
                memmove(m_buf, m_cursor, a), m_cursor = m_buf;
                size_type b = a + fread(m_buf + a, 1, INPUT_BUFFER_SIZE - a, m_file_ptr);
                if (b < INPUT_BUFFER_SIZE) m_end = m_buf + b, *m_end = EOF;
            }
            template <typename Tp, typename BinaryOperation>
            InputHelper &fill_integer(Tp &ret, BinaryOperation op) {
                if (!isdigit(*m_cursor)) return set_bad();
                ret = op(Tp(0), *m_cursor - '0');
                size_type len = 1;
                while (isdigit(*(m_cursor + len))) ret = op(ret * 10, *(m_cursor + len++) - '0');
                m_cursor += len;
                return *this;
            }
            explicit InputHelper(const char *inputFileName) : m_ok(true), m_cursor(m_buf + INPUT_BUFFER_SIZE), m_end(m_buf + INPUT_BUFFER_SIZE) { m_file_ptr = *inputFileName ? fopen(inputFileName, "rt") : stdin; }
            ~InputHelper() { fclose(m_file_ptr); }
            static InputHelper &get_instance() {
                static InputHelper s_obj(input_file);
                return s_obj;
            }
            static bool is_blank(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
            static bool is_endline(char c) { return c == '\n' || c == EOF; }
            const char &getchar_checked() {
                _reserve<1>();
                return *m_cursor;
            }
            const char &getchar_unchecked() const { return *m_cursor; }
            void next() { ++m_cursor; }
            template <typename Tp, typename std::enable_if<std::is_signed<Tp>::value & std::is_integral<Tp>::value>::type * = nullptr>
            InputHelper &operator>>(Tp &num) {
                while (is_blank(getchar_checked())) next();
                _reserve<MAX_INTEGER_SIZE>();
                if (getchar_unchecked() != '-') return fill_integer(num, std::plus<Tp>());
                next();
                return fill_integer(num, std::minus<Tp>());
            }
            template <typename Tp, typename std::enable_if<std::is_unsigned<Tp>::value & std::is_integral<Tp>::value>::type * = nullptr>
            InputHelper &operator>>(Tp &num) {
                while (is_blank(getchar_checked())) next();
                _reserve<MAX_INTEGER_SIZE>();
                return fill_integer(num, std::plus<Tp>());
            }
            template <typename Tp, typename std::enable_if<std::is_floating_point<Tp>::value>::type * = nullptr>
            InputHelper &operator>>(Tp &num) {
                bool neg = false, integer = false, decimal = false;
                while (is_blank(getchar_checked())) next();
                _reserve<MAX_FLOAT_SIZE>();
                if (getchar_unchecked() == '-') {
                    neg = true;
                    next();
                }
                if (!isdigit(getchar_unchecked()) && getchar_unchecked() != '.') return set_bad();
                if (isdigit(getchar_unchecked())) {
                    integer = true;
                    num = getchar_unchecked() - '0';
                    while (next(), isdigit(getchar_unchecked())) num = num * 10 + (getchar_unchecked() - '0');
                }
                if (getchar_unchecked() == '.')
                    if (next(), isdigit(getchar_unchecked())) {
                        if (!integer) num = 0;
                        decimal = true;
                        Tp unit = 0.1;
                        num += unit * (getchar_unchecked() - '0');
                        while (next(), isdigit(getchar_unchecked())) num += (unit *= 0.1) * (getchar_unchecked() - '0');
                    }
                if (!integer && !decimal) return set_bad();
                if (neg) num = -num;
                return *this;
            }
            InputHelper &operator>>(char &c) {
                while (is_blank(getchar_checked())) next();
                if (getchar_checked() == EOF) return set_bad();
                c = getchar_checked(), next();
                return *this;
            }
            InputHelper &operator>>(std::string &s) {
                while (is_blank(getchar_checked())) next();
                if (getchar_checked() == EOF) return set_bad();
                s.clear();
                do {
                    s += getchar_checked();
                    next();
                } while (!is_blank(getchar_checked()) && getchar_unchecked() != EOF);
                return *this;
            }
            explicit operator bool() { return m_ok; }
        };
        struct OutputHelper {
            FILE *m_file_ptr = nullptr;
            char m_buf[OUTPUT_BUFFER_SIZE], *m_end, *m_cursor;
            char m_temp_buf[MAX_FLOAT_SIZE], *m_temp_buf_cursor, *m_temp_buf_dot;
            uint64_t m_float_reserve, m_float_ratio;
            void _write() { fwrite(m_buf, 1, m_cursor - m_buf, m_file_ptr), m_cursor = m_buf; }
            template <size_type BlockSize>
            void _reserve() {
                size_type a = m_end - m_cursor;
                if (a >= BlockSize) return;
                _write();
            }
            OutputHelper(const char *outputFileName, size_type prec = 6) : m_cursor(m_buf), m_end(m_buf + OUTPUT_BUFFER_SIZE), m_temp_buf_cursor(m_temp_buf) { m_file_ptr = *outputFileName ? fopen(outputFileName, "wt") : stdout, precision(prec); }
            static OutputHelper &get_instance() {
                static OutputHelper s_obj(output_file);
                return s_obj;
            }
            ~OutputHelper() { flush(), fclose(m_file_ptr); }
            void precision(size_type prec) { m_float_reserve = prec, m_float_ratio = uint64_t(pow(10, prec)), m_temp_buf_dot = m_temp_buf + prec; }
            OutputHelper &flush() { return _write(), fflush(m_file_ptr), *this; }
            void putchar(const char &c) {
                if (m_cursor == m_end) _write();
                *m_cursor++ = c;
            }
            template <typename Tp, typename std::enable_if<std::is_signed<Tp>::value & std::is_integral<Tp>::value>::type * = nullptr>
            OutputHelper &operator<<(Tp ret) {
                _reserve<MAX_INTEGER_SIZE>();
                size_type len = 0;
                if (ret >= 0)
                    do *(m_cursor + len++) = '0' + ret % 10, ret /= 10;
                    while (ret);
                else {
                    putchar('-');
                    do *(m_cursor + len++) = '0' - ret % 10, ret /= 10;
                    while (ret);
                }
                for (size_type i = 0, j = len - 1; i < j;) std::swap(*(m_cursor + i++), *(m_cursor + j--));
                m_cursor += len;
                return *this;
            }
            template <typename Tp, typename std::enable_if<std::is_unsigned<Tp>::value & std::is_integral<Tp>::value>::type * = nullptr>
            OutputHelper &operator<<(Tp ret) {
                _reserve<MAX_INTEGER_SIZE>();
                size_type len = 0;
                do *(m_cursor + len++) = '0' + ret % 10, ret /= 10;
                while (ret);
                for (size_type i = 0, j = len - 1; i < j;) std::swap(*(m_cursor + i++), *(m_cursor + j--));
                m_cursor += len;
                return *this;
            }
            template <typename Tp, typename std::enable_if<std::is_floating_point<Tp>::value>::type * = nullptr>
            OutputHelper &operator<<(Tp ret) {
                if (ret < 0) {
                    putchar('-');
                    return *this << -ret;
                }
                ret *= m_float_ratio;
                uint64_t integer = ret;
                if (ret - integer >= 0.4999999999) integer++;
                do {
                    *m_temp_buf_cursor++ = '0' + integer % 10;
                    integer /= 10;
                } while (integer);
                if (m_temp_buf_cursor > m_temp_buf_dot) {
                    do putchar(*--m_temp_buf_cursor);
                    while (m_temp_buf_cursor > m_temp_buf_dot);
                    putchar('.');
                } else {
                    putchar('0'), putchar('.');
                    for (size_type i = m_temp_buf_dot - m_temp_buf_cursor; i--;) putchar('0');
                }
                do putchar(*--m_temp_buf_cursor);
                while (m_temp_buf_cursor > m_temp_buf);
                return *this;
            }
            OutputHelper &operator<<(const char &ret) {
                putchar(ret);
                return *this;
            }
            OutputHelper &operator<<(const char *ret) {
                while (*ret) putchar(*ret++);
                return *this;
            }
            OutputHelper &operator<<(const std::string &ret) { return *this << ret.data(); }
        };
        InputHelper &getline(InputHelper &ih, std::string &line) {
            line.clear();
            if (ih.getchar_checked() == EOF) return ih.set_bad();
            while (!InputHelper::is_endline(ih.getchar_checked())) line += ih.getchar_unchecked(), ih.next();
            if (ih.getchar_unchecked() != EOF) ih.next();
            return ih;
        }
    }
}
// -------------------------------end fastio---------------------------------

// --- 全局变量 ---
ll arr[maxn], sarr = 0;
int n, m;

// 图和DFS相关数组
int dep[maxn], dfn[maxn], siz[maxn];
int head[maxn], nxt[maxn], to[maxn];
int dcnt = 0, ecnt = 0;

// 手动栈实现所需的数组和指针
int stack_node[maxn];
int stack_edge[maxn];
int stack_ptr = 0;

void addEdge(int u, int v) {
	to[ecnt] = v;
	nxt[ecnt] = head[u];
	head[u] = ecnt++;
}

void iterative_dfs_manual_stack(int start_node) {
    stack_ptr = 0;

    dep[start_node] = 0;
    dfn[start_node] = ++dcnt;
    siz[start_node] = 1;

    stack_node[stack_ptr] = start_node;
    stack_edge[stack_ptr] = head[start_node];
    stack_ptr++;

    while (stack_ptr > 0) { 
        int u = stack_node[stack_ptr - 1];
        int& edge_idx = stack_edge[stack_ptr - 1];

        if (edge_idx != -1) {
            int v = to[edge_idx];

            edge_idx = nxt[edge_idx];

            dep[v] = dep[u] + 1;
            dfn[v] = ++dcnt;
            siz[v] = 1;
    
            stack_node[stack_ptr] = v;
            stack_edge[stack_ptr] = head[v];
            stack_ptr++;
        } else {
            stack_ptr--; 
            if (stack_ptr > 0) {
                siz[stack_node[stack_ptr - 1]] += siz[u];
            }
        }
    }
}


void solve() {
	ll b;
	fcin >> b;
	if (b >= sarr) {
		fcout << 1 << '\n';
		return;
	}
    // --- 每次查询前的初始化 ---
	ecnt = 0;
	dcnt = 0;
    // 注意：这个循环仍然是 O(N) 的，是性能开销的一部分
	for (int i = 0; i <= n * 2; ++i) head[i] = -1;
	
    // --- O(N) 建图 ---
    int l = 1;
    ll sum = 0;
	for (int i = 1; i <= n * 2; ++i) {
		sum += arr[i];
		while (sum > b) {
			sum -= arr[l++];
		}
		addEdge(l - 1, i);
	}

	iterative_dfs_manual_stack(0);

	int ans = dep[n];
	for (int i = 1; i < n; ++i) {
		if (dfn[i + n] >= dfn[i]) {
			ans = min(ans, dep[i + n] - dep[i]);
		}
		else {
			ans = min(ans, dep[i + n] - dep[i] + 1);
		}
	}
	fcout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	fcin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		fcin >> arr[i];
		sarr += arr[i];
		arr[i + n] = arr[i];
	}
	while (m--) solve();
}