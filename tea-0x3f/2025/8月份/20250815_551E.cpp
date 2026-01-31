#include <bits/stdc++.h>
using namespace std;

struct Block {
    int l, r;
    long long todo;
    unordered_map<long long,int> lp, rp;
    Block(): l(0), r(0), todo(0) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int blockSize = max(1, (int)ceil(sqrt((double)n / 5.0)));
    int B = (n - 1) / blockSize + 1;
    vector<Block> blocks(B);

    auto calc = [&](int L, int R) {
        unordered_map<long long,int> lp; lp.reserve(R - L);
        for (int j = R - 1; j >= L; --j) lp[a[j]] = j;
        unordered_map<long long,int> rp; rp.reserve(R - L);
        for (int j = L; j < R; ++j) rp[a[j]] = j;
        return pair<unordered_map<long long,int>, unordered_map<long long,int>>(move(lp), move(rp));
    };

    for (int i = 0; i < n; i += blockSize) {
        int r = min(i + blockSize, n);
        auto maps = calc(i, r);
        int idx = i / blockSize;
        blocks[idx].l = i;
        blocks[idx].r = r;
        blocks[idx].todo = 0;
        blocks[idx].lp = move(maps.first);
        blocks[idx].rp = move(maps.second);
    }

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int l, r;
            long long v;
            cin >> l >> r >> v;
            --l;
            for (int bi = 0; bi < B; ++bi) {
                Block &b = blocks[bi];
                if (b.r <= l) continue;
                if (b.l >= r) break;
                if (l <= b.l && b.r <= r) {
                    b.todo += v;
                    continue;
                }
                for (int j = b.l; j < b.r; ++j) {
                    a[j] += b.todo;
                    if (l <= j && j < r) a[j] += v;
                }
                b.todo = 0;
                auto maps = calc(b.l, b.r);
                b.lp = move(maps.first);
                b.rp = move(maps.second);
            }
        } else {
            long long x; cin >> x;
            int posL = n;
            for (int bi = 0; bi < B; ++bi) {
                Block &b = blocks[bi];
                long long key = x - b.todo;
                auto it = b.lp.find(key);
                if (it != b.lp.end()) { posL = it->second; break; }
            }
            if (posL == n) {
                cout << -1 << '\n';
                continue;
            }
            for (int bi = B - 1; bi >= 0; --bi) {
                Block &b = blocks[bi];
                long long key = x - b.todo;
                auto it = b.rp.find(key);
                if (it != b.rp.end()) { cout << (it->second - posL) << '\n'; break; }
            }
        }
    }
    return 0;
}
