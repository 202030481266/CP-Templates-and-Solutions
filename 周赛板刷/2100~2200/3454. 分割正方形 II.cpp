#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// 经典扫描线的运用
const int MAXN = 2e5 + 3;

int X[MAXN];

struct ScanLine {
    int l, r, h, mark;
    bool operator < (const ScanLine & rhs) {
        if (h == rhs.h)
            return mark > rhs.mark;
        else return h < rhs.h;
    }
} line[MAXN];

struct Node {
    int l, r, sum, len;
} tree[MAXN << 2];

#define lson rt<<1
#define rson rt<<1|1

void build(int rt, int l, int r) {
    tree[rt].l = l, tree[rt].r = r;
    tree[rt].sum = tree[rt].len = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
}

void pushup(int rt) {
    int l = tree[rt].l, r = tree[rt].r;
    if (tree[rt].sum) {
        tree[rt].len = X[r+1] - X[l];
    }
    else {
        tree[rt].len = tree[lson].len + tree[rson].len;
    }
}

void update(int rt, int L, int R, int c) {
    // [X[l], X[r+1]]
    int l = tree[rt].l, r = tree[rt].r;
    if (X[r+1] <= L || R <= X[l]) return;
    if (L <= X[l] && X[r+1] <= R) {
        tree[rt].sum += c;
        pushup(rt);
        return;
    }
    update(lson, L, R, c);
    update(rson, L, R, c);
    pushup(rt);
}

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        int n = squares.size();
        double tot = 0, l = 0, r = 0;
        for (int i = 0; i < n*8; ++i) {
            // 线段树初始化，不知道为什么lc上出现了bug
            tree[i].l = tree[i].r = tree[i].sum = tree[i].len = 0;
        }
        for (int i = 1; i <= n; ++i) {
            int x = squares[i-1][0], y = squares[i-1][1], w = squares[i-1][2];
            X[2*i-1] = x, X[2*i] = x + w;
            line[2*i-1] = (ScanLine){x, x+w, y, 1};
            line[2*i] = (ScanLine){x, x+w, y+w, -1};
            if (y+w > r) r = y+w;
        }
        n *= 2;
        sort(X + 1, X + 1 + n);
        sort(line + 1, line + 1 + n);
        int m = unique(X + 1, X + 1 + n) - X - 1;
        build(1, 1, m-1);
        vector<double> sq(n+1);
        vector<int> tot_len(n+1);
        double cur = 0;
        // 不管最后一条边
        for (int i = 1; i < n; ++i) {
            update(1, line[i].l, line[i].r, line[i].mark);
            tot_len[i] = tree[1].len;
            cur += 1.0 * tree[1].len * (line[i+1].h - line[i].h);
            sq[i+1] = cur;
        }
        tot = sq[n];
        for (int i = 0; i < 50; ++i) {
            // 二分答案
            double mid = (l+r) / 2.0;
            int j = 1;
            while (j < n && line[j].h <= mid) ++j;
            double sum = sq[j-1] + (mid - line[j-1].h) * tot_len[j-1];
            if (sum >= tot/2) r = mid;
            else l = mid;
        }
        return l;
    }
};