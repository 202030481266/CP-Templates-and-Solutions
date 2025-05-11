#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

int cnt[50007], vis[500007];
int to[50007][2];

class Solution {
public:
    void addEdge(int u, int v) {
        // u->v
        if (to[u][0] == -1) to[u][0] = v;
        else to[u][1] = v;
    }
    long long maxScore(int n, vector<vector<int>>& edges) {
        for (int i = 0; i < n; ++i) {
            cnt[i] = 0;
            vis[i] = 0;
            to[i][0] = to[i][1] = -1;
        }
        for (auto& e : edges) {
            ++cnt[e[0]];
            ++cnt[e[1]];
            addEdge(e[0], e[1]);
            addEdge(e[1], e[0]);
        }
        auto dfs = [&](int u) -> int {
            int cur = u, len = 0;
            while (!vis[cur]) {
                ++len;
                vis[cur] = 1;
                if (to[cur][0] != -1 && !vis[to[cur][0]]) {
                    cur = to[cur][0];
                }
                else if (to[cur][1] != -1 && !vis[to[cur][1]]) {
                    cur = to[cur][1];
                }
            }
            return len;
        };
        vector<int> chains;
        vector<int> circles;
        for (int i = 0; i < n; ++i) {
            if (cnt[i] == 1) {
                int l = dfs(i);
                if (l) chains.push_back(l);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (cnt[i] == 2 && !vis[i]) {
                int l = dfs(i);
                if (l) circles.push_back(l);
            }
        }
        sort(chains.begin(), chains.end());
        sort(circles.begin(), circles.end());
        ll ans = 0, res, x;
        for (int i = (int)circles.size()-1; i >= 0; --i) {
            x = n - circles[i] + 1;
            res = x * (x+1) + x * (x+2) + (x+1) * (x+2);
            for (ll k = x + 3; k <= n; ++k) {
                res = res - (k-1) * (k-2) + k * (k*2-3);
            }
            n -= circles[i];
            ans += res;
        }
        for (int i = (int)chains.size()-1; i >= 0; --i) {
            x = n - chains[i] + 1;
            res = x * (x+1);
            for (ll k = x+2; k <= n; ++k) {
                res = res - (k-1) * (k-2) + k * (k*2-3);
            }
            n -= chains[i];
            ans += res;
        }
        return ans;
    }
};