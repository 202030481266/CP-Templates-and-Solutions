// P4735 最大异或和
// https://www.luogu.com.cn/problem/P4735

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 3e5 + 10;
const int N = maxn * 50;
const int BIT = 30;

int root[maxn * 2], tot, tree[N][2];
int n, m, cnt[N], xor_sum;

int insert(int x, int i) {
    int rt = ++tot;
    tree[rt][0] = tree[i][0];
    tree[rt][1] = tree[i][1];
    cnt[rt] = cnt[i] + 1;
    for (int j = BIT, b, pre = rt, cur; j >= 0; --j) {
        b = (x >> j) & 1;
        i = tree[i][b];
        cur = ++tot;
        tree[cur][0] = tree[i][0];
        tree[cur][1] = tree[i][1];
        cnt[cur] = cnt[i] + 1; 
        tree[pre][b] = cur;
        pre = cur;
    } 
    return rt;
}
int query(int x, int i, int j) {
    int res = 0;
    for (int k = BIT, b; k >= 0; --k) {
        b = (x >> k) & 1;
        if (cnt[tree[j][b ^ 1]] - cnt[tree[i][b ^ 1]] > 0) {
            res += 1<<k;
            j = tree[j][b ^ 1];
            i = tree[i][b ^ 1];
        }
        else {
            j = tree[j][b];
            i = tree[i][b];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    root[0] = insert(0, 0); // 前缀异或和为 0
    for (int i = 1, tmp; i <= n; ++i) {
        cin >> tmp;
        xor_sum ^= tmp;
        root[i] = insert(xor_sum, root[i-1]);
    }
    // [l, r]
    // [l-1,r-1]
    char op;
    for (int i = 1, l, r, num; i <= m; ++i) {
        cin >> op;
        if (op == 'A') {
            cin >> num;
            ++n;
            xor_sum ^= num;
            root[n] = insert(xor_sum, root[n-1]);
        }
        else {
            cin >> l >> r >> num;
            if (l == 1) {
                cout << query(xor_sum ^ num, 0, root[r-1]) << '\n';
            }
            else {
                cout << query(xor_sum ^ num, root[l-2], root[r-1]) << '\n';
            }
        }
    }
}