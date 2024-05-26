#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

// 需要使用0的位置，不能使用位运算
#define lc rt*2
#define rc rt*2+1
#define mid ((l+r)/2)
#define lson lc,l,mid
#define rson rc,mid+1,r
// 这里的大小需要修改
#define Maxn 50010

int a[Maxn<<2];
const int inf = 0x3f3f3f3f;
struct node {
    int ms, ls, rs, s;
} tr[Maxn<<2];
void pushup(int rt) {
    tr[rt].s = max(-inf, tr[lc].s + tr[rc].s);
    tr[rt].ls = max(tr[lc].ls, max(-inf, tr[rc].ls + tr[lc].s));
    tr[rt].rs = max(tr[rc].rs, max(-inf, tr[lc].rs + tr[rc].s));
    tr[rt].ms = max(max(tr[lc].ms, tr[rc].ms), max(-inf, tr[lc].rs + tr[rc].ls));
}
void build(int rt, int l, int r) {
    if (l == r) {
        tr[rt].ls=tr[rt].rs=tr[rt].ms=tr[rt].s=1;
        return;
    }
    build(lson);
    build(rson);
    pushup(rt);
}
void update(int rt, int l, int r, int pos) {
    if (l == r) {
        tr[rt].ls=tr[rt].rs=tr[rt].ms=tr[rt].s=-inf;
        return;
    }
    if (pos <= mid) update(lson, pos);
    else update(rson, pos);
    pushup(rt);
}
node query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tr[rt];
    node x, y, w;
    if (R <= mid) w = query(lson, L, R);
    else if (L > mid) w = query(rson, L, R); 
    else {
        x = query(lson, L, mid);
        y = query(rson, mid+1, R);
        w.s = max(-inf,x.s + y.s);
        w.ms = max(max(x.ms, y.ms),max(-inf,x.rs+y.ls));
        w.ls = max(x.ls, max(-inf,x.s+y.ls));
        w.rs = max(y.rs, max(-inf,y.s+x.rs));
    }
    return w;
}

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        //思路简单，就是判断[0,x]里面的最大字段和是否大于等于y，区分一下左端点即可
        vector<bool> ans;
        int n = min(50000, (int)queries.size()*3);
        build(1,1,n);
        for (auto q : queries) {
            if (q[0] == 1) {
                update(1, 1, n, q[1]); // [0,n]
            }
            else {
                if (q[1]-1 < 1) ans.push_back(q[2]<=1);
                else {
                    if(q[2]==1) ans.push_back(true);//这个地方坑了我两个小时，真的有点傻逼智障了
                    else {
                        node res1 = query(1, 1, n, 1, q[1]-1); // 不包含右端点, 此时区间必然有[0,q[1]]作为线段两端点
                        node res2 = query(1, 1, n, q[1], q[1]); // 包含右端点
                        // cout << res.ms << endl;
                        ans.push_back(res1.ms >= q[2]-1 || res2.ms >= q[2]);
                    }
                }
            }
        }
        return ans;
    }
};