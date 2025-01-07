// 线段树优化DP
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

#define ls rt << 1
#define rs rt << 1 | 1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

const int N = 1e5+10;
int a[N*4];

void push_up(int rt) {
    a[rt] = max(a[ls], a[rs]);
}
void update(int rt, int l, int r, int pos, int val) {
    if (l == r) {
        a[rt] = val;
        return;
    }
    if (pos <= mid) update(lson, pos, val);
    else update(rson, pos, val);
    push_up(rt);
}
int query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return a[rt];
    if (R <= mid) return query(lson, L, R);
    else if (L > mid) return query(rson, L, R);
    else return max(query(lson, L, mid), query(rson, mid+1, R));
}

class Solution {
public:
    int maxPathLength(vector<vector<int>>& coordinates, int k) {
        // 模板题, 分别做一次严格的LIS和LDS
        auto ck = coordinates[k];
        vi xs;
        for (auto c : coordinates) xs.push_back(c[0]);
        sort(all(xs));
        xs.erase(unique(all(xs)), xs.end());
        // 离散化
        for (auto& c : coordinates) {
            c[0] = lower_bound(all(xs), c[0]) - xs.begin();
        }
        // 离散化 y
        vi ys;
        for (auto c : coordinates) ys.push_back(c[1]);
        sort(all(ys));
        ys.erase(unique(all(ys)), ys.end());
        for (auto& c : coordinates) {
            c[1] = lower_bound(all(ys), c[1]) - ys.begin();
        }
        // 排序
        int n = xs.size(), m = ys.size();
        vi g[n];
        for (auto c : coordinates) {
            g[c[0]].push_back(c[1]);
        }
        sort(all(coordinates));
        int kx = lower_bound(all(xs), ck[0]) - xs.begin();
        int ky = lower_bound(all(ys), ck[1]) - ys.begin();
        // 线段树优化 LIS 
        memset(a, 0, sizeof(a));
        for (int i = n-1; i > kx; --i) {
            sort(all(g[i]));
            for (int j = 0; j < g[i].size(); ++j) {
                int mx = query(1, 0, m, g[i][j]+1, m); //[0,m]
                update(1, 0, m, g[i][j], mx+1);
            }
        }
        int lis = query(1, 0, m, ky+1, m);
        memset(a, 0, sizeof(a));
        for (int i = 0; i < kx; ++i) {
            sort(all(g[i]));
            for (int j = g[i].size()-1; j >= 0; --j) {
                int mx = g[i][j] > 0 ? query(1, 0, m, 0, g[i][j]-1) : 0;
                update(1, 0, m, g[i][j], mx+1);
            }
        }
        int lds = ky > 0 ? query(1, 0, m, 0, ky-1) : 0;
        return lis+lds+1;
    }
};
