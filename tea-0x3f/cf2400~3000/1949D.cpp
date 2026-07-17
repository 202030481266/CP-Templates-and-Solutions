// Problem: D. Funny or Scary?
// Contest: Codeforces - European Championship 2024 - Online Mirror (Unrated, ICPC Rules, Teams Preferred)
// URL: https://codeforces.com/problemset/problem/1949/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    // 1. 统计已有 'F' 和 'S' 的数量
    int count_F = 0, count_S = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (grid[i][j] == 'F') count_F++;
            if (grid[i][j] == 'S') count_S++;
        }
    }

    // 2. 保证我们推导的前提: S 的边数 >= F 的边数。
    // 如果 F 更多，我们做一个全局镜像反转，最后再转回来。
    bool swapped = false;
    if (count_F > count_S) {
        swapped = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'F') grid[i][j] = 'S';
                else if (grid[i][j] == 'S') grid[i][j] = 'F';
            }
        }
    }

    // 3. 提取所有的连通块 (把已有连接的点绑定在一起)
    vector<bool> visited(n, false);
    vector<vector<int>> components;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            vector<int> comp;
            vector<int> q = {i};
            visited[i] = true;
            int head = 0;
            while (head < q.size()) {
                int u = q[head++];
                comp.push_back(u);
                for (int v = 0; v < n; ++v) {
                    // 只要有边相连，就属于同一个连通块
                    if (u != v && grid[u][v] != '?' && !visited[v]) {
                        visited[v] = true;
                        q.push_back(v);
                    }
                }
            }
            components.push_back(comp);
        }
    }

    // 4. 使用 DP 挑选连通块，使其总点数等于 ceil(3n/4) 或 ceil(3n/4)+1
    int target1 = (3 * n + 3) / 4; // 向上取整的计算方式
    int target2 = target1 + 1;
    int num_comps = components.size();
    
    // dp[i][j] 表示前 i 个连通块能否凑出大小 j
    vector<vector<bool>> dp(num_comps + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= num_comps; ++i) {
        int size = components[i - 1].size();
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = dp[i - 1][j]; // 不选当前连通块
            if (j >= size && dp[i - 1][j - size]) {
                dp[i][j] = true;     // 选当前连通块
            }
        }
    }

    // 确定 S1 集合最终要凑的目标大小
    int final_target = -1;
    if (dp[num_comps][target1]) {
        final_target = target1;
    } else if (target2 <= n && dp[num_comps][target2]) {
        final_target = target2;
    } else {
        // 兜底策略：寻找最接近目标的合法大小 (根据你的数学推断，这里基本不会触发偏离目标的情况)
        for(int j = target1; j >= 0; j--) {
            if(dp[num_comps][j]) { final_target = j; break; }
        }
    }

    // 5. 回溯 DP 数组，将对应的点加入 S1 集合
    vector<bool> in_s1(n, false);
    int current_sum = final_target;
    for (int i = num_comps; i > 0; --i) {
        int size = components[i - 1].size();
        if (!dp[i - 1][current_sum]) {
            // 说明必定是选了第 i 个连通块才凑出来的 current_sum
            for (int node : components[i - 1]) {
                in_s1[node] = true;
            }
            current_sum -= size;
        }
    }

    // 6. 执行你的核心填表逻辑！
    // 同集合内部填 'S'，跨集合填 'F'
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (grid[i][j] == '?') {
                if (in_s1[i] == in_s1[j]) {
                    grid[i][j] = 'S'; 
                } else {
                    grid[i][j] = 'F'; 
                }
            }
        }
    }

    // 7. 如果最开始做过镜像反转，现在转回来
    if (swapped) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'F') grid[i][j] = 'S';
                else if (grid[i][j] == 'S') grid[i][j] = 'F';
            }
        }
    }

    // 输出最终答案
    for (int i = 0; i < n; ++i) {
        cout << grid[i] << "\n";
    }
}

int main() {
    // 优化输入输出速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}