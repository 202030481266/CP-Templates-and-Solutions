// https://codeforces.com/problemset/problem/1270/B
#include <iostream>
using namespace std;

static constexpr int maxn = 200001;

int a[maxn];

void cf1270B() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i + 1 < n; ++i) {
        if (abs(a[i] - a[i+1]) >= 2) {
            cout << "YES" << '\n';
            cout << i + 1 << ' ' << i + 2 << '\n';
            return;
        }
    }
    cout << "NO" << '\n';
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) cf1270B();
}
