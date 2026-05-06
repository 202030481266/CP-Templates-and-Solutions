class FenwickSet {
private:
    int n, tot;       // n: 值域上限, tot: 当前元素总数
    vector<int> tr;   // 树状数组
    vector<ll> sum;
    int high_bit;     // 倍增搜索的起始位 (2^k)

public:
    FenwickSet(int size) : n(size), tot(0) {
        tr.assign(n + 1, 0);
        sum.assign(n + 1, 0ll);
        high_bit = 1;
        while ((high_bit << 1) <= n) high_bit <<= 1;
    }

    void add(int val, int delta) {
        int s_delta = delta * val;
        tot += delta;
        for (; val <= n; val += val & -val) tr[val] += delta;
        for (; val <= n; val += val & -val) sum[val] += s_delta;
    }

    int ask(int val) {
        int res = 0;
        for (; val > 0; val -= val & -val) res += tr[val];
        return res;
    }

    ll query(int val) {
        ll res = 0;
        for (; val > 0; val -= val & -val) res += sum[val];
        return res;
    }

    // --- 高级接口 ---

    void insert(int val) {
        add(val, 1);
    }

    void erase(int val) {
        if (ask(val) > ask(val - 1)) {
            add(val, -1);
        }
    }

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

    ll kth_sum(int k) {
        if (k > tot) return -1;
        int pos = 0;
        ll s = 0;
        for (int i = high_bit; i > 0; i >>= 1) {
            if (pos + i <= n && tr[pos + i] < k) {
                pos += i
                s += sum[pos];
                k -= tr[pos];
            }
        }
        return s + 1ll * k * (pos + 1);
    }

    int get_max() {
        return tot == 0 ? -1 : kth(tot);
    }

    int get_min() {
        return tot == 0 ? -1 : kth(1);
    }

    int size() { return tot; }
};