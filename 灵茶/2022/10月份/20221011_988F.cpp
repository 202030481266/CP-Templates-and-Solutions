#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18;

// 李超线段树：支持动态插入直线，查询单点最小值
struct LiChaoTree {
    struct Line {
        ll k, b;
        ll eval(int x) { return k * x + b; }
    };

    int range_L, range_R;
    vector<Line> tree;
    vector<bool> has_line; // 标记节点是否有直线

    LiChaoTree(int l, int r) : range_L(l), range_R(r) {
        // 空间开 4 倍
        tree.resize(4 * (r - l + 1));
        has_line.resize(4 * (r - l + 1), false);
    }

    void add_line(ll k, ll b, int node, int l, int r) {
        Line new_line = {k, b};
        if (!has_line[node]) {
            tree[node] = new_line;
            has_line[node] = true;
            return;
        }

        int mid = (l + r) / 2;
        ll val_new = new_line.eval(mid);
        ll val_old = tree[node].eval(mid);

        // 如果新直线在中点更优，交换，保证 tree[node] 存的是中点最优的
        if (val_new < val_old) {
            swap(tree[node], new_line);
        }

        // 剪枝：如果区间长度为1，没必要往下走了
        if (l == r) return;

        // 判断左右端点，决定新直线（被交换下来的那条）应该下放到哪边
        if (new_line.eval(l) < tree[node].eval(l)) {
            add_line(new_line.k, new_line.b, node * 2, l, mid);
        } else if (new_line.eval(r) < tree[node].eval(r)) {
            add_line(new_line.k, new_line.b, node * 2 + 1, mid + 1, r);
        }
    }

    void add(ll k, ll b) {
        add_line(k, b, 1, range_L, range_R);
    }

    ll query(int x, int node, int l, int r) {
        if (!has_line[node]) return INF;
        
        ll val = tree[node].eval(x);
        if (l == r) return val;

        int mid = (l + r) / 2;
        if (x <= mid) {
            return min(val, query(x, node * 2, l, mid));
        } else {
            return min(val, query(x, node * 2 + 1, mid + 1, r));
        }
    }

    ll query(int x) {
        return query(x, 1, range_L, range_R);
    }
};

void solve() {
    int dst, n, m;
    cin >> dst >> n >> m;

    // 记录每个单位路段是否下雨: rain[i] 表示 i -> i+1 是否下雨
    vector<bool> is_raining(dst + 1, false);
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        for (int j = l; j < r; ++j) {
            is_raining[j] = true;
        }
    }

    // 记录每个位置有的伞（只存最小重量即可，或者全存也行，反正李超树能处理）
    // 这里为了方便，用 vector 存每个位置的所有伞
    vector<vector<int>> umbrellas(dst + 1);
    for (int i = 0; i < m; ++i) {
        int x, w;
        cin >> x >> w;
        if (x <= dst) {
            umbrellas[x].push_back(w);
        }
    }

    // dp[i] 表示到达位置 i 的最小代价
    vector<ll> dp(dst + 1, INF);
    dp[0] = 0;

    // 初始化李超树，定义域 [0, dst]
    LiChaoTree cht(0, dst);

    for (int i = 0; i < dst; ++i) {
        // 1. 如果当前到达了 i，且 dp[i] 合法，我们可以捡起这里所有的伞
        if (dp[i] != INF) {
            for (int w : umbrellas[i]) {
                // 插入直线: Cost = w * x + (dp[i] - w * i)
                // 斜率 k = w, 截距 b = dp[i] - w * i
                cht.add(w, dp[i] - (ll)w * i);
            }
        }

        // 2. 尝试走向 i+1
        if (!is_raining[i]) {
            // 如果没下雨，可以空手走，代价不变
            if (dp[i] != INF) {
                dp[i + 1] = min(dp[i + 1], dp[i]);
            }
        }
        
        // 3. 无论下不下雨，都可以尝试用手里已有的伞走过去（查询 CHT）
        // 如果是下雨天，这是唯一的路径（除非上面没更新 dp[i+1]）
        ll cost_with_umbrella = cht.query(i + 1);
        dp[i + 1] = min(dp[i + 1], cost_with_umbrella);
    }

    if (dp[dst] == INF) cout << -1 << endl;
    else cout << dp[dst] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}