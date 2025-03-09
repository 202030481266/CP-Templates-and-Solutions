#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

#define ls (rt << 1)
#define rs (rt << 1 | 1)   
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r 

const int maxn = 1e5 + 10;
int mn[maxn<<2]; 

void pushup(int rt) {
    mn[rt] = min(mn[ls], mn[rs]);
}

void build(int rt, int l, int r, vector<int>& a) {
    if (l == r) {
        mn[rt] = a[l];
        return;
    }
    build(lson, a);
    build(rson, a);
    pushup(rt);
}

void update(int rt, int l, int r, int p, int val) {
    if (l == r) {
        mn[rt] = val;
        return;
    }
    if (p <= mid) update(lson, p, val);
    else update(rson, p, val);
    pushup(rt);
}

int query(int rt, int l, int r, int val) {
    if (l == r) {
        return l;
    }
    if (mn[ls] <= val) return query(lson, val);
    else return query(rson, val);
}
class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = fruits.size();
        // frutis的线段树
        build(1, 0, n-1, fruits);
        
        int ans = 0;
        for (int q : baskets) {
            if (mn[1] > q) ans++;
            else {
                int p = query(1, 0, n-1, q);
                update(1, 0, n-1, p, inf);
            }
        }
        return ans;
    }
};