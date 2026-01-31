// https://www.luogu.com.cn/problem/P3755
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int maxn = 100007;

int n, m, cnt;
ll ans[maxn];
array<int, 4> a[maxn*5], temp[maxn*5];

void add(int x, int y, int w, int id) {
    a[++cnt][0] = x;    
    a[cnt][1] = y;
    a[cnt][2] = w;
    a[cnt][3] = id;
}

void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    cdq(l, mid);
    cdq(mid + 1, r);
    int p1 = l, p2 = mid + 1, p = l;
    ll c = 0;
    while (p2 <= r) {
        while (p1 <= mid && a[p1][1] <= a[p2][1]) {
            if (a[p1][3] == 0) {
                c += a[p1][2];
            }
            p1++;
        }
        if (a[p2][3] > 0) ans[a[p2][3]] += a[p2][2] * c;
        p2++;
    }
    p1 = l, p2 = mid + 1;
    while (p1 <= mid && p2 <= r) {
        if (a[p1][1] <= a[p2][1]) temp[p++] = a[p1++];
        else temp[p++] = a[p2++];
    }
    while (p1 <= mid) temp[p++] = a[p1++];
    while (p2 <= r) temp[p++] = a[p2++];
    for (int i = l; i <= r; ++i) a[i] = temp[i];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x, y, w; i <= n; ++i) {
        cin >> x >> y >> w;
        add(x, y, w, 0);
    }
    for (int i = 1, x1, y1, x2, y2; i <= m; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        add(x2, y2, 1, i);
        add(x2, y1 - 1, -1, i);
        add(x1 - 1, y2, -1, i);
        add(x1 - 1, y1 - 1, 1, i);
    }
    sort(a + 1, a + 1 + cnt, [&](const auto& x, const auto& y){
        return x[0] != y[0] ? x[0] < y[0] : x[3] < y[3];
    });
    cdq(1, cnt);
    for (int i = 1; i <= m; ++i) {
        cout << ans[i] << '\n';
    }
}