#pragma once
#include <cassert>
#include <vector>

namespace cp {
// 区间加、区间求和，O(log n)。所有区间为 [l,r)，注意 sum 与 delta*长度溢出。
// 仿射、区间赋值等复杂标记请用 docs/recipes.md 中的 ACL 入口。
class RangeAddSum {
    int n_;
    std::vector<long long> sum_, lazy_;
    void build(int p, int l, int r, const std::vector<long long>& a) {
        if (r - l == 1) { sum_[p] = a[l]; return; }
        int m = l + (r - l) / 2;
        build(p * 2, l, m, a);
        build(p * 2 + 1, m, r, a);
        pull(p);
    }
    void pull(int p) { sum_[p] = sum_[p * 2] + sum_[p * 2 + 1]; }
    void apply(int p, int length, long long value) {
        sum_[p] += value * length;
        lazy_[p] += value;
    }
    void push(int p, int l, int r) {
        int m = l + (r - l) / 2;
        apply(p * 2, m - l, lazy_[p]);
        apply(p * 2 + 1, r - m, lazy_[p]);
        lazy_[p] = 0;
    }
    void add(int p, int l, int r, int ql, int qr, long long value) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) { apply(p, r - l, value); return; }
        push(p, l, r);
        int m = l + (r - l) / 2;
        add(p * 2, l, m, ql, qr, value);
        add(p * 2 + 1, m, r, ql, qr, value);
        pull(p);
    }
    long long query(int p, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return sum_[p];
        push(p, l, r);
        int m = l + (r - l) / 2;
        return query(p * 2, l, m, ql, qr) + query(p * 2 + 1, m, r, ql, qr);
    }
public:
    explicit RangeAddSum(int n = 0) : n_(n), sum_(4 * n + 4), lazy_(4 * n + 4) {}
    explicit RangeAddSum(const std::vector<long long>& a) : RangeAddSum(int(a.size())) {
        if (n_) build(1, 0, n_, a);
    }
    void add(int l, int r, long long value) {
        assert(0 <= l && l <= r && r <= n_);
        if (l < r) add(1, 0, n_, l, r, value);
    }
    long long sum(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        return l == r ? 0 : query(1, 0, n_, l, r);
    }
};
} // namespace cp
