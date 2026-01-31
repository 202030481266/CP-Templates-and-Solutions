// https://acm.hdu.edu.cn/showproblem.php?pid=1823
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int N = 107;
const int M = 1007;

int tree[N<<2][M<<2], n, m;
int a, b; // height
double c, d;

void innerBuild(int root, int rt, int l, int r) {
    tree[root][rt] = -1;
    if (l == r) return;
    int mid = (l+r) >> 1;
    innerBuild(root, rt<<1, l, mid);
    innerBuild(root, rt<<1|1, mid+1, r);
}
void innerUpdate(int root, int rt, int l, int r, int pos, int val) {
    if (l == r) {
        tree[root][rt] = max(tree[root][rt], val);
        return;
    }
    int mid = (l+r) >> 1;
    if (pos <= mid) innerUpdate(root, rt<<1, l, mid, pos, val);
    else innerUpdate(root, rt<<1|1, mid+1, r, pos, val);
    tree[root][rt] = max(tree[root][rt<<1], tree[root][rt<<1|1]);
}
int innerQuery(int root, int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[root][rt];
    int mid = (l+r) >> 1;
    if (R <= mid) return innerQuery(root, rt<<1, l, mid, L, R);
    else if (L > mid) return innerQuery(root, rt<<1|1, mid+1, r, L, R);
    else return max(innerQuery(root, rt<<1, l, mid, L, mid), innerQuery(root, rt<<1|1, mid+1, r, mid+1, R));
}
void outerBuild(int root, int l, int r) {
    innerBuild(root, 1, 0, 1000);
    if (l == r) return;
    int mid = (l+r) >> 1;
    outerBuild(root<<1, l, mid);
    outerBuild(root<<1|1, mid+1, r);
}
void outerUpdate(int root, int l, int r, int h, int pos, int val) {
    innerUpdate(root, 1, 0, 1000, pos, val);
    if (l == r) {
        return;
    }
    int mid = (l+r) >> 1;
    if (h <= mid) outerUpdate(root<<1, l, mid, h, pos, val);
    else outerUpdate(root<<1|1, mid+1, r, h, pos, val);
}
int outerQuery(int root, int l, int r, int hL, int hR, int L, int R) {
    if (hL <= l && r <= hR) {
        return innerQuery(root, 1, 0, 1000, L, R);
    }
    int mid = (l+r) >> 1;
    if (hR <= mid) return outerQuery(root<<1, l, mid, hL, hR, L, R);
    else if (hL > mid) return outerQuery(root<<1|1, mid+1, r, hL, hR, L, R);
    else return max(outerQuery(root<<1, l, mid, hL, mid, L, R), outerQuery(root<<1|1, mid+1, r, mid+1, hR, L, R));
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    while (true) {
        cin >> m;
        if (m == 0) break;
        outerBuild(1, 0, 100);
        char op;
        while (m--) {
            cin >> op;
            if (op == 'I') {
                cin >> a >> c >> d;
                a -= 100;
                c *= 10;
                d *= 10;
                outerUpdate(1, 0, 100, a, c, d);
            }
            else {
                cin >> a >> b >> c >> d;
                a -= 100, b -= 100;
                c *= 10, d *= 10;
                if (a > b) swap(a, b);
                if (c > d) swap(c, d);
                int ans = outerQuery(1, 0, 100, a, b, c, d);
                if (ans == -1) cout << -1 << '\n';
                else cout << fixed << setprecision(1) << ans / 10.0 << '\n';
            }
        }
    }
}