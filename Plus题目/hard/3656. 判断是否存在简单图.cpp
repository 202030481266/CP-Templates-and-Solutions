#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 100005;
int fenwick[maxn], n;

inline int lowbit(int i) {
    return i & -i;
}

void update(int p, int val) {
    while (p <= n) {
        fenwick[p] += val;
        p += lowbit(p);
    }
}

int query(int p) {
    int res = 0;
    while (p) {
        res += fenwick[p];
        p -= lowbit(p);
    }
    return res;
}

int find_by_prefix(int S) {
    int pos = 0;
    int acc = 0;
    int mask = 1;
    while ((mask << 1) <= n) mask <<= 1;
    for (int k = mask; k > 0; k >>= 1) {
        if (pos + k <= n && acc + fenwick[pos + k] < S) {
            acc += fenwick[pos + k];
            pos += k;
        }
    }
    return pos + 1;
}

class Solution {
public:
    bool simpleGraphExists(vector<int>& degrees) {
        ranges::sort(degrees);
        n = degrees.size();
        for (int i = 0; i <= n; ++i) fenwick[i] = 0;
        for (int i = 0; i < n; ++i) {
            if (i - 1 >= 0) update(i + 1, degrees[i] - degrees[i - 1]);
            else update(i + 1, degrees[i]);
        }
        for (int i = n; i >= 1; --i) {
            int x = query(i);
            if (!x) break;
            int left = find_by_prefix(1), right, val; // [left, i)
            if (i - left < x) return false;
            // [i - x, i - 1] down 1
            // find the left , right of number a[i - x], because we want down its left part to maintain the ascend order
            val = query(i - x);
            left = find_by_prefix(val);
            right = min(find_by_prefix(val + 1), i);
            int len = right - i + x; // [left, left + len) <- [i - x, right)
            update(left, -1);
            update(left + len, 1);
            if (right < i) update(right, -1);
            // update(i, 1);
        }
        return true;
    }
};