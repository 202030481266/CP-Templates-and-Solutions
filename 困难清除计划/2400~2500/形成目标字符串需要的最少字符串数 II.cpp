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

vi Z(string &b) {
    int m = b.size();
    vi z(m);
    z[0] = m;
    for (int i = 1, c = 1, r = 1; i < m; ++i) {
        int len = (i < r ? min(r - i, z[i - c]) : 0);
        while (i + len < m && b[i + len] == b[len]) ++len;
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
    return z;
}
vi ex_kmp(string &a, string &b, vi& z) {
    int n = a.size(), m = b.size();
    vi e(n);
    for (int i = 0, c = 0, r = 0; i < n; ++i) {
        int len = (i < r ? min(z[i - c], r - i) : 0);
        while (i + len < n && len < m && a[i + len] == b[len]) ++len;
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        e[i] = len;
    }
    return e;
}
#define ls rt << 1
#define rs rt << 1 | 1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
int a[50010*4];
void pushup(int rt) {
    a[rt] = min(a[ls], a[rs]);
}
void update(int rt, int l, int r, int pos, int val) {
    if (l == r) {
        a[rt] = min(a[rt], val);
        return;
    }
    if (pos <= mid) update(lson, pos, val);
    else update(rson, pos, val);
    pushup(rt);
}
int query(int rt, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return a[rt];
    int res = INF;
    if (ql <= mid) res = min(res, query(lson, ql, qr));
    if (qr > mid) res = min(res, query(rson, ql, qr));
    return res;
}
class Solution {
public:
    int minValidStrings(vector<string>& words, string target) {
        int n = words.size(), m = target.size();
        vector<vi> wz(n);
        for (int i = 0; i < n; ++i) {
            wz[i] = Z(words[i]);
        }
        vector<vi> ex(n);
        for (int i = 0; i < n; ++i) {
            ex[i] = ex_kmp(target, words[i], wz[i]);
        }
        memset(a, 0x3f, sizeof(a));   
        // 假设区间设置就是 [1,len]
        // dp[i] = min(dp[i+x]+1), x = 1~len
        // [i+1, i+len]
        // 线段树可以加速
        // 枚举后缀
        update(1, 0, m, m, 0); // dp[m] = 0
        int mn, val;
        for (int i = m-1; i >= 0; --i) {
            mn = INF, val = INF;
            for (int j = 0; j < n; ++j) {
                // [i,m)
                int len = min(m-i, ex[j][i]);
                // [i+1,i+len]
                val = query(1, 0, m, i+1, i+len)+1;
                if (val < mn) mn = val;
            }
            update(1, 0, m, i, mn);
        }
        int ans = query(1, 0, m, 0, 0);
        return ans == INF ? -1 : ans;
    }
};