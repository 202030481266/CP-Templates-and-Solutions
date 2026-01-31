#include <bits/stdc++.h>
using namespace std;

int cnt[4200000], arr[1000003];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, mx = 0;
    cin >> n;
    memset(cnt, -1, sizeof(cnt));
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        mx = max(mx, arr[i]);
        cnt[arr[i]] = arr[i];
    }
    int w = bit_width(1u * mx);
    int mask = (1 << w) - 1;
    for (int i = 0; i < w; ++i) {
        for (int s = 0; s < 1 << w; ++s) {
            if (s >> i & 1 && cnt[s] == -1) cnt[s] = cnt[s ^ 1 << i];
        }
    }
    for (int i = 0; i < n; ++i) cout << cnt[mask ^ arr[i]] << ' ';
}