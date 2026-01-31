// https://www.luogu.com.cn/problem/P3332
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 5e4 + 7;
const int N = maxn * 230;
ll sum[N], lazy[N], c;
int ls[N], rs[N], root[maxn<<2], tot = 0;
int n, m;
vector<int> arr;
vector<vector<ll>> qs;
int get(int x) {
    return lower_bound(arr.begin(), arr.end(), x) - arr.begin() + 1;
}
void pushdown(int rt, int l, int r) {
    if (lazy[rt] != 0) {
        if (ls[rt] == 0) ls[rt] = ++tot;
        if (rs[rt] == 0) rs[rt] = ++tot;
        lazy[ls[rt]] += lazy[rt];
        lazy[rs[rt]] += lazy[rt];
        int mid = (l+r) >> 1;
        sum[ls[rt]] += lazy[rt] * (mid-l+1);
        sum[rs[rt]] += lazy[rt] * (r-mid);
        lazy[rt] = 0;
    }
}
int innerUpdate(int rt, int l, int r, int L, int R) {
    if (rt == 0) rt = ++tot;
    if (L <= l && r <= R) {
        sum[rt] += (r-l+1);
        lazy[rt]++;
        return rt;
    }
    pushdown(rt, l, r);
    int mid = (l+r) >> 1;
    if (R <= mid) ls[rt] = innerUpdate(ls[rt], l, mid, L, R);
    else if (L > mid) rs[rt] = innerUpdate(rs[rt], mid+1, r, L, R);
    else {
        ls[rt] = innerUpdate(ls[rt], l, mid, L, mid);
        rs[rt] = innerUpdate(rs[rt], mid+1, r, mid+1, R);
    }
    sum[rt] = sum[ls[rt]] + sum[rs[rt]];
    return rt;
}
ll innerQuery(int rt, int l, int r, int L, int R) {
    if (rt == 0) return 0;
    if (L <= l && r <= R) return sum[rt];
    pushdown(rt, l, r);
    int mid = (l+r) >> 1;
    if (R <= mid) return innerQuery(ls[rt], l, mid, L, R);
    else if (L > mid) return innerQuery(rs[rt], mid+1, r, L, R);
    else return innerQuery(ls[rt], l, mid, L, mid) + innerQuery(rs[rt], mid+1, r, mid+1, R);
}
void outerUpdate(int rt, int l, int r, int L, int R, int c) {
    root[rt] = innerUpdate(root[rt], 1, n, L, R);
    if (l == r) return;
    int mid = (l+r) >> 1;
    if (c <= mid) outerUpdate(rt<<1, l, mid, L, R, c);
    else outerUpdate(rt<<1|1, mid+1, r, L, R, c);
}
int outerQuery(int rt, int l, int r, int L, int R, ll k) {
    if (l == r) return l;
    int mid = (l+r) >> 1;
    ll rs_sum = innerQuery(root[rt<<1|1], 1, n, L, R);
    if (rs_sum >= k) return outerQuery(rt<<1|1, mid+1, r, L, R, k);
    else return outerQuery(rt<<1, l, mid, L, R, k-rs_sum);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, op, l, r; i <= m; ++i) {
        cin >> op >> l >> r >> c;
        qs.push_back({op, l, r, c});
        if (op == 1) arr.push_back(c);
    }
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    m = arr.size();
    for (auto& q : qs) {
        if (q[0] == 1) {
            outerUpdate(1, 1, m, q[1], q[2], get(q[3]));
        }
        else {
            int ans = outerQuery(1, 1, m, q[1], q[2], q[3]);
            cout << arr[ans-1] << '\n';
        }
    }
}