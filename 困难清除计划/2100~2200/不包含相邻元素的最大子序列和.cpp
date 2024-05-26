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
#define Maxn 50010

struct node {
    ll xx,yy,xy,yx,mx;
} tr[Maxn<<2];

// 动态规划
void pushup(int rt) {
    tr[rt].xy = max(tr[lc].xy+tr[rc].xy,tr[lc].xx+max(tr[rc].xy,tr[rc].yy));
    tr[rt].yx = max(tr[rc].yx+tr[lc].yx,tr[rc].xx+max(tr[lc].yx,tr[lc].yy));
    tr[rt].xx = max(tr[lc].xy+tr[rc].xx,tr[lc].xx+max(tr[rc].yx,tr[rc].xx));
    tr[rt].yy = max(tr[lc].yy+tr[rc].xy,tr[lc].yx+max(tr[rc].yy,tr[rc].xy));
    tr[rt].mx = max(tr[lc].mx, tr[rc].mx);
    tr[rt].mx = max(tr[rt].mx, max(tr[lc].xx,tr[lc].yx)+tr[rc].mx);
    tr[rt].mx = max(tr[rt].mx, max(tr[lc].xy,tr[lc].yy)+max(tr[rc].xx,tr[rc].xy));
    tr[rt].mx = max(tr[rt].mx, max(tr[rc].xx,tr[rc].xy)+tr[lc].mx);
    tr[rt].mx = max(tr[rt].mx, max(tr[rc].yy,tr[rc].yx)+max(tr[lc].xx,tr[lc].yx));
}
void build(int rt, int l, int r, vector<int>& a) {
    if (l==r) {
        tr[rt].xx=tr[rt].xy=tr[rt].yx=0;
        tr[rt].yy=tr[rt].mx=a[l];
        return;
    }
    build(lson,a);
    build(rson,a);
    pushup(rt);
}
void update(int rt, int l, int r, int p, int v) {
    if (l==r) {
        tr[rt].xx=tr[rt].xy=tr[rt].yx=0;
        tr[rt].yy=tr[rt].mx=v;
        return;
    }
    if (p<=mid) update(lson,p,v);
    else update(rson,p,v);
    pushup(rt);
}

class Solution {
public:
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        // 显然负数是不重要的，我们只需要考虑正数构成的连续子数组如何维护，这个是难点
        // 使用线段树应该是最优秀的解法
        int n = nums.size();
        build(1,0,n-1,nums);
        ll ans = 0;
        for (auto q : queries) {
            update(1,0,n-1,q[0],q[1]);
            if (tr[1].mx > 0)
                ans = (ans + tr[1].mx + mod) % mod;
        }
        return ans;
    }
};