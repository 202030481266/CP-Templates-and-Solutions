#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 100005;

int n, q;
int arr[MAXN];

// 分块核心数组
int S;                  // 块大小 (通常是 sqrt(N))
int bel[MAXN];          // bel[i] 表示 i 所属的块编号
int L[MAXN];            // L[b] 表示块 b 的左边界
int R[MAXN];            // R[b] 表示块 b 的右边界

// 状态数组
int steps[MAXN];        // steps[i]: 跳出当前块需要的步数
int next_pos[MAXN];     // next_pos[i]: 跳出当前块后落在哪
int last_node[MAXN];    // last_node[i]: 跳出当前块前，踩在这个块里的最后一个节点

// 核心操作：重构块内的信息（时间复杂度 O(√N)）
void rebuild(int p) {
    int b = bel[p];
    int start_idx = L[b];
    
    // 只有 p 以及 p 前面的节点可能受影响，所以从 p 倒推到块首
    for (int i = p; i >= start_idx; --i) {
        int nxt = i + arr[i];
        
        if (nxt > R[b]) {
            // 情况 A：一步直接跳出当前块
            steps[i] = 1;
            next_pos[i] = nxt;
            last_node[i] = i; // 跳出前踩的最后一个节点就是自己
        } else {
            // 情况 B：跳到了当前块内的另一个节点 nxt
            // 那么直接继承 nxt 的信息即可（因为是从后往前遍历的，nxt 的信息已经算好了）
            steps[i] = steps[nxt] + 1;
            next_pos[i] = next_pos[nxt];
            last_node[i] = last_node[nxt];
        }
    }
}

int main() {
    // 开启极速 IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }

    // 1. 初始化分块边界
    S = sqrt(n);
    int blocks = (n + S - 1) / S;
    for (int i = 1; i <= blocks; ++i) {
        L[i] = (i - 1) * S + 1;
        R[i] = min(i * S, n);
        for (int j = L[i]; j <= R[i]; ++j) {
            bel[j] = i;
        }
    }

    // 2. 初始计算每个块的信息（倒着建）
    for (int i = blocks; i >= 1; --i) {
        rebuild(R[i]); // 对每个块从最右端一直算到最左端
    }

    // 3. 处理查询
    for (int i = 0; i < q; ++i) {
        int op;
        cin >> op;
        
        if (op == 0) {
            int p, b;
            cin >> p >> b;
            arr[p] = b;
            // O(√N) 重构 p 所在的那个局部块
            rebuild(p); 
            
        } else if (op == 1) {
            int x;
            cin >> x;
            
            int ans_steps = 0;
            int ans_root = x;
            
            // O(√N) 块与块之间的大跳跃
            while (x <= n) {
                ans_steps += steps[x];       // 累加跳出这个块需要的步数
                ans_root = last_node[x];     // 记录离开这个块前，踩住的最后一个点
                x = next_pos[x];             // 瞬间转移到下一个落地点
            }
            
            // 完美输出你需要的格式： 根节点 深度
            cout << ans_root << " " << ans_steps << "\n";
        }
    }

    return 0;
}