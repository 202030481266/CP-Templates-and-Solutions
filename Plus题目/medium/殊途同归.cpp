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

int path[1010][1010];

class Solution {
public:
    int numberOfPaths(int n, vector<vector<int>>& corridors) {
        memset(path, 0, sizeof(path));
        vector<int> rank(n);
        for (auto& e : corridors) {
            --e[0],--e[1];
            ++rank[e[0]];
            ++rank[e[1]];
        }
        vector<int> g[n];
        for (auto& e : corridors) {
            if (rank[e[0]] < rank[e[1]] || rank[e[0]]==rank[e[1]] && e[0] < e[1]) {
                g[e[0]].push_back(e[1]);
                path[e[0]][e[1]] = 1;
            }
            else { 
                g[e[1]].push_back(e[0]);
                path[e[1]][e[0]] = 1;
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int u : g[i]) {
                for (int v : g[u]) {
                    if (path[i][v]) ++ans;
                }
            }
        }
        return ans;
    }
};