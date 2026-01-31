// https://www.luogu.com.cn/problem/P3380
// 树状数组套线段树
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 5e4 + 7;
const int N = maxn * 200;
const int INF = 2147483647;
int n, m, ls[N], rs[N], sum[N], arr[maxn], root[maxn], tot = 0;
int ops[maxn][4], a[maxn<<1], len = 0;
int addgroup[maxn], subgroup[maxn], len_add = 0, len_sub = 0;

int lowbit(int i) {
    return i & -i;
}
int get(int x) { // 值域范围：[1, len]
    return lower_bound(a + 1, a + 1 + len, x) - a;
}
int innerUpdate(int rt, int l, int r, int pos, int val) {
    if (!rt) rt = ++tot;
    if (l == r) {
        sum[rt] += val;
        return rt;
    }
    int mid = (l+r) >> 1;
    if (pos <= mid) ls[rt] = innerUpdate(ls[rt], l, mid, pos, val);
    else rs[rt] = innerUpdate(rs[rt], mid+1, r, pos, val);
    sum[rt] = sum[ls[rt]] + sum[rs[rt]];
    return rt;
}
void update(int pos, int val) { // 这里修改的值就是arr[pos]
    for (int i = pos; i <= n; i += lowbit(i)) {
        root[i] = innerUpdate(root[i], 1, len, arr[pos], val);
    }
}
int innerQuery(int l, int r, int pos) { // 查找小于pos的数字的个数
    if (l == r) return 0;
    int mid = (l + r) >> 1;
    // sum[0] = 0，所以不用怕addgroup中的根为0
    if (pos <= mid) {
        for (int i = 1; i <= len_add; ++i) {
            addgroup[i] = ls[addgroup[i]];
        }
        for (int i = 1; i <= len_sub; ++i) {
            subgroup[i] = ls[subgroup[i]];
        }
        return innerQuery(l, mid, pos);
    }
    else {
        int res = 0;
        for (int i = 1; i <= len_add; ++i) {
            res += sum[ls[addgroup[i]]];
            addgroup[i] = rs[addgroup[i]];
        }
        for (int i = 1; i <= len_sub; ++i) {
            res -= sum[ls[subgroup[i]]];
            subgroup[i] = rs[subgroup[i]];
        }
        return res + innerQuery(mid + 1, r, pos);
    }
}
int small(int l, int r, int x) {
    // 数组区间[l, r] 中小于x的数字的个数
    len_add = len_sub = 0;
    for (int i = r; i > 0; i -= lowbit(i)) {
        addgroup[++len_add] = root[i];
    }
    for (int i = l-1; i > 0; i -= lowbit(i)) {
        subgroup[++len_sub] = root[i];
    }
    return innerQuery(1, len, x);
}
int innerKth(int l, int r, int k) { // 查找第K大
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int left_sum = 0;
    for (int i = 1; i <= len_add; ++i) {
        left_sum += sum[ls[addgroup[i]]];
    }
    for (int i = 1; i <= len_sub; ++i) {
        left_sum -= sum[ls[subgroup[i]]];
    }
    if (left_sum >= k) {
        for (int i = 1; i <= len_add; ++i) {
            addgroup[i] = ls[addgroup[i]];
        }
        for (int i = 1; i <= len_sub; ++i) {
            subgroup[i] = ls[subgroup[i]];
        }
        return innerKth(l, mid, k);
    }
    else {
        for (int i = 1; i <= len_add; ++i) {
            addgroup[i] = rs[addgroup[i]];
        }
        for (int i = 1; i <= len_sub; ++i) {
            subgroup[i] = rs[subgroup[i]];
        }
        return innerKth(mid + 1, r, k - left_sum);
    }
}
int findKth(int l, int r, int k) {
    len_add = len_sub = 0;
    for (int i = r; i > 0; i -= lowbit(i)) {
        addgroup[++len_add] = root[i];
    }
    for (int i = l-1; i > 0; i -= lowbit(i)) {
        subgroup[++len_sub] = root[i];
    }
    return innerKth(1, len, k);
}
int find_pre(int l, int r, int x) {
    int rank = small(l, r, x) + 1;
    if (rank == 1) return -INF;
    return findKth(l, r, rank-1);
}
int find_next(int l, int r, int x) {
    if (x == len) return INF;
    int rank = small(l, r, x+1);
    if (rank >= r-l+1) return INF;
    return findKth(l, r, rank + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        a[++len] = arr[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> ops[i][0];
        if (ops[i][0] == 3) {
            cin >> ops[i][1] >> ops[i][2];
            a[++len] = ops[i][2];
        }
        else {
            cin >> ops[i][1] >> ops[i][2] >> ops[i][3];
            if (ops[i][0] != 2) {
                a[++len] = ops[i][3];
            }
        }
    }
    sort(a + 1, a + 1 + len);
    int tmp = 1;
    for (int i = 2; i <= len; ++i) {
        if (a[i] != a[tmp]) {
            a[++tmp] = a[i];
        }
    }
    len = tmp;
    for (int i = 1; i <= n; ++i) {
        arr[i] = get(arr[i]);
        update(i, 1);
    }
    for (int i = 1, ans; i <= m; ++i) {
        if (ops[i][0] == 1) {
            ops[i][3] = get(ops[i][3]);
            cout << small(ops[i][1], ops[i][2], ops[i][3]) + 1 << '\n';
        }
        else if (ops[i][0] == 2) {
            ans = findKth(ops[i][1], ops[i][2], ops[i][3]);
            cout << a[ans] << '\n'; 
        }
        else if (ops[i][0] == 3) {
            int p = ops[i][1];
            update(p, -1);
            arr[p] = get(ops[i][2]);
            update(p, 1);
        }
        else if (ops[i][0] == 4) {
            ops[i][3] = get(ops[i][3]);
            ans = find_pre(ops[i][1], ops[i][2], ops[i][3]);
            if (ans == -INF) cout << ans << '\n';
            else cout << a[ans] << '\n';
        }
        else {
            ops[i][3] = get(ops[i][3]);
            ans = find_next(ops[i][1], ops[i][2], ops[i][3]);
            if (ans == INF) cout << ans << endl;
            else cout << a[ans] << '\n';
        }
    }
    return 0;
}