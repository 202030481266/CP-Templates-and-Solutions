#include <bits/stdc++.h>

using namespace std;

// https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm in O(V^3)
// 全局最小割的算法，因为使用了固定顺序的维护点集的方法来不断扩展（类似于prim)，所以算法复杂度比较好
pair<int, vector<int>> min_cut(vector<vector<int>> &cap) {
    // 使用邻接矩阵
    // 初始化割为inf
    int best_cap = numeric_limits<int>::max();
    vector<int> best_cut; // 记录每一个s-t割
    int n = cap.size();
    vector<vector<int>> v(n);
    for (int i = 0; i < n; ++i)
        v[i].push_back(i);
    vector<int> w(n);
    // exist数组判断是否已经合并了，合并之后就不存在了
    vector<bool> exist(n, true);
    vector<bool> in_a(n); // 维护点集A
    for (int ph = 0; ph < n - 1; ++ph) {
        // 开始新一轮的计算s-t最小割
        // 只需要进行n-1轮合并
        fill(in_a.begin(), in_a.end(), false);
        fill(w.begin(), w.end(), 0);
        // 第ph次合并只需寻找到n-ph-2个节点
        for (int it = 0, prev; it < n - ph; ++it) {
            int sel = -1;
            // sel为寻找到与A集合最大边权的点
            for (int i = 0; i < n; ++i)
                if (exist[i] && !in_a[i] && (sel == -1 || w[i] > w[sel])) {
                    sel = i;
                }
            if (it == n - ph - 1) {
                // 此时剩下一个节点t(sel)和集合A
                // prev为最后集合A中最后加入的一个节点，即s
                if (w[sel] < best_cap) {
                    best_cap = w[sel];
                    best_cut = v[sel];
                }
                // 合并节点s和t为st，实现中st为s，t消失
                // 同时更新新的权值，变为一个单独的块
                v[prev].insert(v[prev].end(), v[sel].begin(), v[sel].end());
                for (int i = 0; i < n; ++i) {
                    cap[i][prev] += cap[sel][i];
                    cap[prev][i] += cap[sel][i];
                }
                exist[sel] = false;
            } else {
                in_a[sel] = true;
                // 因为sel与i之间连接，所以要切掉i和集合A，就要增加权值cap[sel][i]
                for (int i = 0; i < n; ++i)
                    w[i] += cap[sel][i];
                prev = sel;
            }
        }
    }
    return {best_cap, best_cut};
}

// usage example
int main() {
    vector<vector<int>> capacity{{0, 1, 1, 0}, {1, 0, 1, 1}, {1, 1, 0, 1}, {0, 1, 1, 0}};
    auto [cap, cut] = min_cut(capacity);
    cout << cap << endl;
    for (int v : cut)
        cout << v << " ";
    cout << endl;
}
