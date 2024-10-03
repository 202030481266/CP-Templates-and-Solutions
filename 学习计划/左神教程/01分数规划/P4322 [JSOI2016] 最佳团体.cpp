#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

const int maxn = 2505;
int K, N, P[maxn], S[maxn], siz[maxn], dfn[maxn];
double dp[maxn][maxn]; 
vector<int> g[maxn];
int cnt = 0;

void dfs(int u) {
    dfn[cnt++] = u;
    siz[u] = 1;
    for (int v : g[u]) {
        dfs(v);
        siz[u] += siz[v];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> K >> N;
    int fa;
    for (int i = 1; i <= N; ++i) {
        cin >> S[i] >> P[i];
        cin >> fa;
        g[fa].push_back(i);
    }
    dfs(0);
    double l = 0, r = 10000;
    for (int iter = 0; iter < 32; ++iter) {
        double mid = (l+r) / 2;
        for (int i = 0; i <= N+1; ++i) {
            for (int j = 1; j <= K; ++j) dp[i][j] = -2e9;
        }
        for (int i = 0; i <= N+1; ++i) dp[i][0] = 0;
        for (int i = N; i >= 1; --i) { 
            for (int j = K; j >= 1; --j) {
                dp[i][j] = max(dp[i+siz[dfn[i]]][j], dp[i+1][j-1]+P[dfn[i]]-mid*S[dfn[i]]);
            }
        }
        if (dp[1][K] >= 0) l = mid;
        else r = mid;
    }
    cout << fixed << setprecision(3) << l << '\n';
    return 0;
}