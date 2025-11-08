#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int maxn = 2e5 + 7;
static constexpr int mod = 1e9 + 7;
static constexpr int maxmat = 40; // 最大矩阵维度

int n, base, stride;

struct Mat {
    int n, m;
    int a[maxmat * maxmat]; // 使用一维静态数组

    Mat() : n(0), m(0) { }

    Mat(int _n, int _m) : n(_n), m(_m) {
        memset(a, 0, sizeof(int) * n * m);
    }

    // 内联访问函数，编译器会优化掉函数调用开销
    inline int& at(int i, int j) {
        return a[i * m + j];
    }

    inline const int& at(int i, int j) const {
        return a[i * m + j];
    }

    inline void make_unit() {
        assert(n == m);
        for (int i = 0; i < n; i++)  {
            for (int j = 0; j < n; j++) {
                at(i, j) = (i == j);
            }
        }
    }

    inline Mat operator + (const Mat &b) const {
        assert(n == b.n && m == b.m);
        Mat ans(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                ans.at(i, j) = (at(i, j) + b.at(i, j)) % mod;
            }
        }
        return ans;
    }

    inline Mat operator - (const Mat &b) const {
        assert(n == b.n && m == b.m);
        Mat ans(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                ans.at(i, j) = (at(i, j) - b.at(i, j) + mod) % mod;
            }
        }
        return ans;
    }

    inline Mat operator * (const Mat &b) const {
        assert(m == b.n);
        Mat ans(n, b.m);
        // 优化的循环顺序：i-k-j，提高缓存命中率
        for(int i = 0; i < n; i++) {
            for(int k = 0; k < m; k++) {
                int aik = at(i, k);
                if (aik == 0) continue; // 跳过零元素
                for(int j = 0; j < b.m; j++) {
                    ans.at(i, j) = (ans.at(i, j) + 1LL * aik * b.at(k, j)) % mod;
                }
            }
        }
        return ans;
    }

    inline Mat pow(long long k) const {
        assert(n == m);
        Mat ans(n, n), t = *this;
        ans.make_unit();
        while (k) {
            if (k & 1) ans = ans * t;
            t = t * t;
            k >>= 1;
        }
        return ans;
    }

    inline Mat& operator += (const Mat& b) { return *this = (*this) + b; }
    inline Mat& operator -= (const Mat& b) { return *this = (*this) - b; }
    inline Mat& operator *= (const Mat& b) { return *this = (*this) * b; }
};

ll quick_pow(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

void solve() {
    cin >> n >> base >> stride;
    if (n == 1) {
        cout << stride << '\n';
        return;
    }
    ll tot = quick_pow(2 * stride + 1, n - 1);
    if (base == 0) {
        cout << tot * stride % mod << '\n';
        return;
    }
    // [0, base - 1]
    tot = tot * (base + stride) % mod;
    Mat A(base, base);
    for (int i = 0; i < base; ++i) {
        for (int j = 0; j < base; ++j) {
            if (abs(i - j) <= stride) A.at(i, j) = 1;
        }
    }
    // X^i = A * X^{i-1}
    Mat X(base, 1);
    for (int i = 0; i < base; ++i) X.at(i, 0) = 1;
    X = A.pow(n - 1) * X;
    for (int i = 0; i < base; ++i) tot = ((tot - X.at(i, 0)) % mod + mod) % mod;
    cout << tot << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
