// 构造技巧：一个数字的最小质因数

#include <bits/stdc++.h>
using namespace std;

vector<int> generate_primes_linear_time(int n) {
    vector<int> lp(n + 1);
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= n; ++j)
            lp[i * primes[j]] = primes[j];
    }
    return primes;
}
void test_all_primes() {
    auto p = generate_primes_linear_time(1000);
    vector<int> is_prime(1000);
    for (int& v : p) is_prime[v] = 1;
    set<int> s;
    for (int i = 4; i <= 1000; ++i) {
        if (!is_prime[i]) {
            for (int j = 2; j * j <= i; ++j) {
                if (i % j == 0) {
                    s.insert(j);
                    break;
                }
            }
        }
    }
    for (int v : s) cout << v << '\t';
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    // 总是可以发现一点就是，最大的数字的最小质因数一定不会超过31,如果超过了，那么一定就是大于1000
    vector<int> primes{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    vector<bool> use(primes.size());
    vector<int> color(primes.size());
    for (int& x : a) {
        for (int i = 0; i < primes.size(); ++i) {
            if (x % primes[i] == 0) {
                use[i] = true;
                x = i;
                break;
            }
        }
    }
    int m = 0;
    for (int i = 0; i < primes.size(); ++i)
        if (use[i]) {
            color[i] = ++m;
        }
    cout << m << '\n';
    for (int i = 0; i < a.size(); ++i) {
        cout << color[a[i]];
        cout << (i == a.size() - 1 ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}