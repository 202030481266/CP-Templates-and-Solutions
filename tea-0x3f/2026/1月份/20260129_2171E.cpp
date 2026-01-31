#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;

bool test(const vi& arr, int n) {
    for (int i = 1; i <= n; ++i) {
        if (arr[i] == 0) {
            cout << "\033[31mAnswer contains zero!\033[0m" << endl;
            for (int v : arr) cout << v << ' '; cout << endl;
            return false;
        }
    }
    int cnt = 0;
    for (int i = 2; i <= n - 1; ++i) {
        if (gcd(arr[i], arr[i - 1]) == 1 && gcd(arr[i], arr[i + 1]) == 1 && gcd(arr[i - 1], arr[i + 1]) == 1) ++cnt;
    }
    if (cnt <= 6) return true;
    else {
        cout << "\033[31mCnt over 6:" << cnt << "\033[0m" << endl;
        return false;
    }
}

void solve() {
    int n;
    cin >> n;
    vi use(n + 1);
    vi ans(n + 1);
    vi a2, a3;
    for (int i = 2; i <= n; ++i) {
        if (i % 3 == 0) a3.push_back(i);
        else if (i % 2 == 0) a2.push_back(i);
    }
    if (a3.size() >= 2) swap(a3[0], a3[1]); // 3 6 -> 6 3
    vi a;
    for (int v : a2) a.push_back(v);
    for (int v : a3) a.push_back(v);
    for (int i = 2, j = 0; i + 1 <= n && j + 1 < (int)a.size(); i += 3, j += 2) {
        ans[i] = a[j];
        ans[i + 1] = a[j + 1];
        use[a[j]] = use[a[j + 1]] = 1;
    }
    int p = 1;
    for (int i = 1; i <= n; ++i) {
        if (ans[i]) continue;
        while (p <= n && use[p]) ++p;
        ans[i] = p;
        use[p] = 1;
    }
    // if (test(ans, n)) cout << "\033[32mAccepted\033[0m" << endl;
    // else cout << "\033[31mWrong Answer\033[0m" << endl;
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    cout << '\n';
}
        

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // bruteforce();
    int t;
    cin >> t;
    while (t--) solve();
}
