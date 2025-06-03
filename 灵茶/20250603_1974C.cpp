// https://codeforces.com/problemset/problem/1974/C
#include <bits/stdc++.h>
using ll = long long;
using namespace std;

static constexpr int maxn = 200007;
int n, a[maxn], ids[maxn];
array<int, 3> arr[200000];

ll check() {
    int p = 0; 
    ll res = 0;    
    while (p < n) {
        int i = p + 1, j = p;
        while (i < n && arr[ids[i]][0] == arr[ids[p]][0] && arr[ids[i]][1] == arr[ids[p]][1]) ++i;
        ll c = 0;
        while (j < i) {
            int k = j + 1;
            while (k < i && arr[ids[k]][2] == arr[ids[j]][2]) ++k;
            res += c * (k - j);
            c += k - j;
            j = k;
        }
        p = i;
    }
    return res;
}

void cf1974C() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i + 2 < n; ++i) {
        arr[i] = {a[i], a[i+1], a[i+2]};
    }
    n -= 2;
    // (0, 1), 2
    iota(ids, ids + n, 0);
    sort(ids, ids + n, [&](int i, int j){return arr[i] < arr[j];});
    ll ans = 0;
    ans += check();
    // (0, 2), 1
    for (int i = 0; i < n; ++i) swap(arr[i][1], arr[i][2]);
    iota(ids, ids + n, 0);
    sort(ids, ids + n, [&](int i, int j){return arr[i] < arr[j];});
    ans += check();
    // (1, 2), 0
    for (int i = 0; i < n; ++i) swap(arr[i][0], arr[i][2]);
    iota(ids, ids + n, 0);
    sort(ids, ids + n, [&](int i, int j){return arr[i] < arr[j];});
    ans += check();
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) cf1974C();
}