// https://www.spoj.com/problems/SKYLINE/
// 此题非常巧妙构造：https://blog.csdn.net/m0_51156601/article/details/143353665?spm=1001.2014.3001.5501

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

const ll mod = 1e6;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    vector<int> a;
    while (true) {
        cin >> n;
        if (n) a.push_back(n);
        else break;
    }
    int mx = *max_element(a.begin(), a.end());
    vector<ll> dp(mx+1);
    dp[0] = 1;
    for (int i = 1; i <= mx; ++i) {
        for (int j = 0; j < i; ++j) {
            dp[i] = (dp[i] + dp[j] * dp[i-1-j] % mod) % mod;
        }
    }
    for (int v : a) cout << dp[v] << '\n';
    return 0;
}