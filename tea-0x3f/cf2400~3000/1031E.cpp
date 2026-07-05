// Problem: E. Triple Flips
// Contest: Codeforces - Technocup 2019 - Elimination Round 2
// URL: https://codeforces.com/problemset/problem/1031/E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>

using namespace std;

// 只有两种本质不同的操作：
// 111
// 1001001

// 可以使用上面的方法造出单个1！这说明长度大于等于7后面的所有的1都一定可以构造出来
//  1001001
//  1110000
//  0111000
//->0000001

// 3 窗口
// 101->10101
// 100->1001001
// 111->111
// 110-> ? can't choose

// 6 窗口 -> 最多 2 步搞定
//  110000
//->100010001
//->01001001

// 我们每次处理 6 个元素，预计算证明最大跨度只需不到 12
// 为保证绝对安全，我们赋予滑动窗口最大跨度为 14
const int MAX_SPAN = 14;

// 存储 64 种状态对应的消除操作序列
vector<vector<array<int, 3>>> moves(64);
bool precomputed = false;

// 预处理：暴力找出 64 种 6 元素前缀的消除方案
void precompute() {
    if (precomputed) return;
    precomputed = true;
    
    vector<array<int, 3>> ops;
    // 生成所有合法操作 (x, y, z) 满足等差且范围在 MAX_SPAN 内
    for (int i = 0; i <= MAX_SPAN; i++) {
        for (int d = 1; i + 2 * d <= MAX_SPAN; d++) {
            ops.push_back({i, i + d, i + 2 * d});
        }
    }
    
    // 尝试只用 1 次操作
    for (auto op : ops) {
        int mask = 0;
        for (int k : op) {
            if (k < 6) mask ^= (1 << k);
        }
        if (mask > 0 && moves[mask].empty()) {
            moves[mask] = {op};
        }
    }
    
    // 尝试使用 2 次操作（制造碰撞）
    for (auto op1 : ops) {
        for (auto op2 : ops) {
            int mask = 0;
            for (int k : op1) if (k < 6) mask ^= (1 << k);
            for (int k : op2) if (k < 6) mask ^= (1 << k);
            
            if (mask > 0 && moves[mask].empty()) {
                moves[mask] = {op1, op2};
            }
        }
    }
}

void solve() {
    int n;
    if (!(cin >> n)) return;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    precompute();

    vector<array<int, 3>> ans;
    int i = 0;
    
    // 阶段 1：主体数组贪心消除，保证不超过 n/3 的界限
    while (i + MAX_SPAN < n) {
        if (a[i] == 0) {
            i++;
            continue;
        }
        
        int mask = 0;
        for (int j = 0; j < 6; j++) {
            if (a[i + j]) mask |= (1 << j);
        }
        
        // 查表并应用操作
        for (auto op : moves[mask]) {
            ans.push_back({i + op[0], i + op[1], i + op[2]});
            a[i + op[0]] ^= 1;
            a[i + op[1]] ^= 1;
            a[i + op[2]] ^= 1;
        }
        i += 6;
    }

    // 阶段 2：尾部处理。剩余数组长度 M <= 14，直接进行状态压缩 BFS
    int M = n - i;
    int start_mask = 0;
    for (int j = 0; j < M; j++) {
        if (a[i + j]) start_mask |= (1 << j);
    }

    if (start_mask != 0) {
        vector<int> dist(1 << M, -1);
        vector<int> parent(1 << M, -1);
        vector<array<int, 3>> parent_op(1 << M);
        
        queue<int> q;
        q.push(start_mask);
        dist[start_mask] = 0;
        
        // 生成仅作用于尾部的所有合法操作
        vector<array<int, 3>> valid_ops;
        for (int x = 0; x < M; x++) {
            for (int d = 1; x + 2 * d < M; d++) {
                valid_ops.push_back({x, x + d, x + 2 * d});
            }
        }
        
        // 跑最短路寻找变回 0 的方法
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            if (u == 0) break; // 已经全部清零
            
            for (auto op : valid_ops) {
                int v = u ^ (1 << op[0]) ^ (1 << op[1]) ^ (1 << op[2]);
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    parent_op[v] = op;
                    q.push(v);
                }
            }
        }
        
        // 如果 BFS 无法到达全 0，说明无解
        if (dist[0] == -1) {
            cout << "NO\n";
            return;
        }
        
        // 回溯提取最短路径上的操作
        int curr = 0;
        vector<array<int, 3>> tail_ops;
        while (curr != start_mask) {
            int p = parent[curr];
            tail_ops.push_back(parent_op[curr]);
            curr = p;
        }
        // 应用尾部操作
        for (auto op : tail_ops) {
            ans.push_back({i + op[0], i + op[1], i + op[2]});
        }
    }

    // 输出答案
    cout << "YES\n";
    cout << ans.size() << "\n";
    for (auto op : ans) {
        // 题目要求输出的是 1-based 的坐标
        cout << op[0] + 1 << " " << op[1] + 1 << " " << op[2] + 1 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}