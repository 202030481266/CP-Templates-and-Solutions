#include <bits/stdc++.h>

using namespace std;
namespace FastIO {
    constexpr int BUFSIZE = 1 << 20; // 1MB缓冲区
    char ibuf[BUFSIZE], obuf[BUFSIZE];
    char *p1 = ibuf, *p2 = ibuf;
    char *p3 = obuf;

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
    inline void write(const string &s) {
        for (char c: s) pc(c);
    }

    // 输出C风格字符串
    inline void write(const char *s) {
        while (*s) pc(*s++);
    }

    // 读取整数（支持负数）
    template<typename T>
    inline enable_if_t<is_integral_v<T>, bool> read(T &x) {
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
    inline enable_if_t<is_floating_point_v<T>, bool> read(T &x) {
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
            } else if (c == '+') {
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
    inline enable_if_t<is_integral_v<T> > write(T x) {
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
    inline enable_if_t<is_floating_point_v<T> > write(T x, int precision = 6) {
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
        auto int_part = static_cast<long long>(x);
        write(int_part);

        // 输出小数点和小数部分
        if (precision > 0) {
            pc('.');
            x -= int_part;
            for (int i = 0; i < precision; i++) {
                x *= 10;
                int digit = static_cast<int>(x);
                pc('0' + digit); // NOLINT(*-narrowing-conversions)
                x -= digit;
            }
        }
    }

    // 输出整数并换行
    template<typename T>
    inline enable_if_t<is_integral_v<T> > writeln(T x) {
        write(x);
        pc('\n');
    }

    // 输出浮点数并换行
    template<typename T>
    inline enable_if_t<is_floating_point_v<T> > writeln(T x, int precision = 6) {
        write(x, precision);
        pc('\n');
    }

    // 读取字符串（读到空白字符为止）
    inline bool read(string &s) {
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
    inline bool getline(string &s) {
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
    inline void writeln(const string &s) {
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
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 200005;
static constexpr int MAXM = 200005;

int n, m, height[MAXN];
ll dis[MAXN];
int head[MAXN], to[MAXM << 1], nxt[MAXM << 1], weight[MAXM << 1], ecnt = 0;

void addEdge(int u, int v, int w) {
    to[++ecnt] = v;
    nxt[ecnt] = head[u];
    weight[ecnt] = w;
    head[u] = ecnt;
}

int main() {
    read(n);
    read(m);
    for (int i = 1; i <= n; ++i) read(height[i]);
    for (int i = 1, u, v; i <= m; ++i) {
        read(u);
        read(v);
        if (height[u] < height[v]) {
            addEdge(u, v, height[v] - height[u]);
            addEdge(v, u, 0);
        }
        else {
            addEdge(u, v, 0);
            addEdge(v, u, height[u] - height[v]);
        }
    }
    for (int i = 1; i <= n; ++i) dis[i] = 0x3f3f3f3f3f3f3f3f;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.emplace(0, 1);
    dis[1] = 0;
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dis[u]) continue;
        for (int i = head[u]; i; i = nxt[i]) {
            if (dis[to[i]] > d + weight[i]) {
                dis[to[i]] = d + weight[i];
                pq.emplace(dis[to[i]], to[i]);
            }
        }
    }
    ll ans = 0;
    for (int i = 2; i <= n; ++i) {
        if (height[i] < height[1] && dis[i] < 0x3f3f3f3f3f3f3f3f) {
            ans = max(ans, height[1] - height[i] - dis[i]);
        }
    }
    writeln(ans);
}