#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 250007;
static constexpr int maxb = 505;

// 根号分治 + bfs搜索

int n, bnum, mx[maxb], vis[maxn];
int bl[maxb], br[maxb], b[maxn];
struct rock {
    int x, y, m, p, r;
    ll dis;
} rocks[maxn];

ll hypot(const rock& a, const rock& b) {
    ll dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> rocks[0].x >> rocks[0].y >> rocks[0].p >> rocks[0].r;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> rocks[i].x >> rocks[i].y >> rocks[i].m >> rocks[i].p >> rocks[i].r;
        rocks[i].dis = hypot(rocks[i], rocks[0]);
    }
    sort(rocks + 1, rocks + n + 1, [&](const rock& a, const rock& b) {
        return a.m < b.m;
    });
    int blen = sqrt(n);
    bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= bnum; ++i) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(n, i * blen);
        mx[i] = rocks[br[i]].m;
        sort(rocks + bl[i], rocks + br[i] + 1, [&](const rock& a, const rock& b){
            return a.dis < b.dis;
        });
    }
    for (int i = 1; i <= n; ++i) {
        b[i] = (i - 1) / blen + 1;
    }
    queue<int> q;
    q.push(0);
    vis[0] = 1;
    int ans = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ++ans;
        ll du = 1ll * rocks[u].r * rocks[u].r;
        for (int i = 1; i <= bnum; ++i) {
            if (mx[i] <= rocks[u].p) { // 整体只会扫一遍
                while (bl[i] <= br[i] && rocks[bl[i]].dis <= du) {
                    if (!vis[bl[i]]) {
                        vis[bl[i]] = 1;
                        q.push(bl[i]);
                    }
                    bl[i]++;
                }
            }
            else {
                // 最多暴力搜索一个块
                for (int j = bl[i]; j <= br[i]; ++j) {
                    if (rocks[j].dis <= du && rocks[j].m <= rocks[u].p) {
                        if (!vis[j]) {
                            vis[j] = 1;
                            q.push(j);
                        }
                    }
                }
                break;
            }
        }
    }
    cout << ans - 1 << endl;
}