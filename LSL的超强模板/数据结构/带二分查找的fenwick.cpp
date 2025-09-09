struct Fenwick {
    int n;
    vector<int> t;

    explicit Fenwick(int _n): n(_n), t(n+1, 0) {}

    static inline int lowbit(int x) {
        return x & -x;
    }

    void init(int N) {
        n = N;
        for (int i = 1; i <= n; i++) {
            t[i] = 0;
        }
    }

    void add(int i, int v) {
        for (; i <= n; i += lowbit(i)) {
            t[i] += v;
        }
    }

    int sum(int i) const {
        int s = 0;
        for (; i > 0; i -= lowbit(i)) {
            s += t[i];
        }
        return s;
    }

    int find_by_prefix(int S) const {
        int pos = 0;
        int acc = 0;
        int mask = 1;
        while ((mask << 1) <= n) mask <<= 1;
        for (int k = mask; k > 0; k >>= 1) {
            if (pos + k <= n && acc + t[pos + k] < S) {
                acc += t[pos + k];
                pos += k;
            }
        }
        return pos + 1;
    }
};
