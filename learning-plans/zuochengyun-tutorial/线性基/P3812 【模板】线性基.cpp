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

const int maxn = 60;
int n;
ll base[maxn];


int main() {
    cin >> n;
    ll tmp, ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        for (int j = 50; j >= 0 && tmp; --j) {
            if ((tmp & (1ll<<j))) {
                if (base[j]) tmp ^= base[j];
                else {
                    base[j] = tmp;
                    break;
                }
            }
        }
    }
    for (int i = 50; i >= 0; --i) {
        if (base[i]) ans = max(ans, ans ^ base[i]);
    }
    cout << ans << endl;
    return 0;
}