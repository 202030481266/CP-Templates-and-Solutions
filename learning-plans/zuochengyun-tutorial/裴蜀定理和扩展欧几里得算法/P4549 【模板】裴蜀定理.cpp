#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'



int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, a;
    cin >> n;
    int g = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a;
        g = gcd(g, a);
    }
    cout << g << endl;
    return 0;
}