// https://www.luogu.com.cn/problem/P3810

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100007;
static constexpr int maxv = 200007;

int fenwick[maxv];
int n, m;
array<int, 4> arr[maxn], temp[maxn];
int ans[maxn], cnt[maxn];

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int v) {
    for (int i = x; i <= m; i += lowbit(i)) {
        fenwick[i] += v;
    }
}

int query(int x) {
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        sum += fenwick[i];
    }
    return sum;
}

void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    cdq(l, mid);
    cdq(mid + 1, r);
    int p1 = l, p2 = mid + 1;
    while (p2 <= r) {
        while (p1 <= mid && arr[p1][2] <= arr[p2][2]) {
            add(arr[p1++][3], 1);
        }
        ans[arr[p2][0]] += query(arr[p2][3]);
        p2++;
    }
    for (int i = l; i < p1; ++i) add(arr[i][3], -1);
    p1 = l, p2 = mid + 1;
    int p = l;
    while (p1 <= mid && p2 <= r) {
        if (arr[p1][2] <= arr[p2][2]) {
            temp[p++] = arr[p1++];
        }
        else {
            temp[p++] = arr[p2++];
        }
    }
    while (p1 <= mid) {
        temp[p++] = arr[p1++];
    }
    while (p2 <= r) {
        temp[p++] = arr[p2++];
    }
    for (int i = l; i <= r; ++i) {
        arr[i] = temp[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        arr[i][0] = i;
        cin >> arr[i][1] >> arr[i][2] >> arr[i][3];
    }
    sort(arr + 1, arr + n + 1, [](const array<int, 4>& x, const array<int, 4>& y){
        return (x[1] != y[1] ? x[1] < y[1] : x[2] != y[2] ? x[2] < y[2] : x[3] < y[3]);
    });
    int i = 1;
    while (i <= n) {
        int j = i;
        while (j <= n && arr[j][1] == arr[i][1] && arr[j][2] == arr[i][2] && arr[j][3] == arr[i][3]) {
            ++j;
        }
        for (int k = i; k < j; ++k) {
            ans[arr[k][0]] = j - k - 1;
        }
        i = j;
    }
    cdq(1, n);
    for (int i = 1; i <= n; ++i) {
        cnt[ans[i]]++;
    }
    for (int i = 0; i < n; ++i) {
        cout << cnt[i] << "\n";
    }
}