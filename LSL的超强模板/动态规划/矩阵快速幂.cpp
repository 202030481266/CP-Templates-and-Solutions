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