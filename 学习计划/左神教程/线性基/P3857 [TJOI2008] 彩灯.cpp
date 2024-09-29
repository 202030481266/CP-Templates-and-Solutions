#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;


int main() {
    int n, m;
    cin >> n >> m;
    vector<ll> b;
    ll tmp;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        tmp = 0;
        for (int j = n-1; j >= 0; --j) {
            if (s[j] == 'O') tmp = (tmp << 1) + 1;
            else tmp <<= 1;
        }
        for (ll k : b) {
            tmp = min(tmp, tmp ^ k);
        }
        if (tmp) b.push_back(tmp);
    }
    int N = b.size();
    cout << (1ll << N)%2008 << '\n';
}