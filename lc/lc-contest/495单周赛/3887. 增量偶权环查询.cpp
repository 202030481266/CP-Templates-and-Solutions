#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 100005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int fa[MAXN], dis[MAXN];

int find(int x) {
    if (x == fa[x]) return x;
    int f = fa[x];
    int ff = find(f);
    dis[x] = dis[x] ^ dis[f];
    fa[x] = ff;
    return ff;
}

class Solution {
public:
    int numberOfEdgesAdded(int n, vector<vector<int>>& edges) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            fa[i] = i;
            dis[i] = 0;
        }
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            int fu = find(u);
            int fv = find(v);
            if (fu != fv) {
                fa[fu] = fv;
                dis[fu] = dis[u] ^ dis[v] ^ w;
                ++ans;
            }
            else {
                if (dis[u] ^ dis[v] ^ w) continue;
                ++ans;
            }
        }
        return ans;
    }
};
