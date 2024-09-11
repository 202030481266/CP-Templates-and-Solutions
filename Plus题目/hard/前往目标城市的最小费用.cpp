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

#define tiii tuple<int,int,int>
#define g0(t) get<0>(t)
#define g1(t) get<1>(t)
#define g2(t) get<2>(t)
#define mt3(a,b,c) make_tuple(a,b,c)


const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;


class Solution {
public:
    int minimumCost(int n, vector<vector<int>>& highways, int discounts) {
        // 状态空间, dijkstra
        // 本质上是一个分层图的思考方法，搜索状态是一样的
        int m = highways.size(), dis[n][discounts+1], vis[n][discounts+1];
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        vector<pii> g[n];
        for (auto& e : highways) {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v,w);
            g[v].emplace_back(u,w);
        }
        priority_queue<tiii, vector<tiii>, greater<tiii>> q;
        q.emplace(0,0,discounts);
        dis[0][discounts] = 0;
        while (!q.empty()) {
            auto [d, u, x] = q.top();
            q.pop();
            if (d != dis[u][x] || vis[u][x]) continue;
            vis[u][x] = 1;
            for (auto [v, w] : g[u]) {
                if (dis[v][x] > d + w) {
                    dis[v][x] = d + w;
                    q.emplace(dis[v][x], v, x);
                }
                if (x > 0 && dis[v][x-1] > d + w / 2) {
                    dis[v][x-1] = d + w / 2;
                    q.emplace(dis[v][x-1], v, x-1);
                }
            }
        }
        int ans = INF;
        for (int i = 0; i <= discounts; ++i) {
            if (ans > dis[n-1][i]) ans = dis[n-1][i];
        }
        return ans == INF ? -1 : ans;
    }
};