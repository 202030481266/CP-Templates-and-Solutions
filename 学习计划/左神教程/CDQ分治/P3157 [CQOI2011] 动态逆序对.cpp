// https://www.luogu.com.cn/problem/P3157
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int maxn = 100007;
static constexpr int maxm = 50007;

int n, m, mp[maxn];
ll fenwick[maxn], ans[maxn]; 
array<int, 4> arr[maxn+maxm];
array<int, 4> temp[maxn+maxm];

int lowbit(int i) {
    return i & -i;
}

void add(int x, ll v) {
    for (int i = x; i <= n; i += lowbit(i)) {
        fenwick[i] += v;
    }
}

ll query(int x) {
    ll res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += fenwick[i];
    }
    return res;
}

void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    cdq(l, mid);
    cdq(mid + 1, r);
    int p1 = l, p2 = mid + 1;
    while (p2 <= r) {
        while (p1 <= mid && arr[p1][1] < arr[p2][1]) {
            add(arr[p1][2], arr[p1][3]);
            ++p1;
        }
        ans[arr[p2][0]] += 1ll * arr[p2][3] * (query(n) - query(arr[p2][2]));
        ++p2;
    }
    for (int i = l; i < p1; ++i) {
        add(arr[i][2], -arr[i][3]);
    }
    p1 = mid, p2 = r;
    while (p2 >= mid + 1) {
        while (p1 >= l && arr[p1][1] > arr[p2][1]) {
            add(arr[p1][2], arr[p1][3]);
            --p1;
        }
        ans[arr[p2][0]] += 1ll * arr[p2][3] * query(arr[p2][2] - 1);
        --p2;
    }
    for (int i = mid; i > p1; --i) {
        add(arr[i][2], -arr[i][3]);
    }
    p1 = l, p2 = mid + 1;
    int p = l;
    while (p1 <= mid && p2 <= r) {
        if (arr[p1][1] < arr[p2][1]) temp[p++] = arr[p1++];
        else temp[p++] = arr[p2++];
    }
    while (p1 <= mid) temp[p++] = arr[p1++];
    while (p2 <= r) temp[p++] = arr[p2++];
    for (int i = l; i <= r; ++i) arr[i] = temp[i];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;    
    for (int i = 1; i <= n; ++i) {
        arr[i][0] = 0; // ans idx
        arr[i][1] = i; // val idx
        cin >> arr[i][2]; // val
        arr[i][3] = 1; // change
        mp[arr[i][2]] = i;
    }
    for (int i = 1; i <= m; ++i) {
        arr[n+i][0] = i;
        cin >> arr[n+i][2];
        arr[n+i][1] = mp[arr[n+i][2]];
        arr[n+i][3] = -1;
    }
    cdq(1, n + m);
    for (int i = 0; i < m; ++i) {
        if (i) ans[i] += ans[i-1];
        cout << ans[i] << '\n';
    }
}