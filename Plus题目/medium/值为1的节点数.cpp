#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;


class Solution {
public:
    int numberOfNodes(int n, vector<int>& queries) {
        vector<int> color(n+1);
        for (int q : queries) color[q] ^= 1;

        int ans = 0;

        function<void(int, int)> dfs = [&](int u, int sum) {
            sum ^= color[u];
            if (sum & 1) ++ans;
            if (2*u <= n) dfs(2*u, sum);
            if (2*u+1 <= n) dfs(2*u+1, sum);
        };

        dfs(1,0);
        return ans;
    }
};