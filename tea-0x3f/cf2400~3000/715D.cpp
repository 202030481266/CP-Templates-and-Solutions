// Problem: D. Create a Maze
// Contest: Codeforces - Codeforces Round 372 (Div. 1)
// URL: https://codeforces.com/problemset/problem/715/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <vector>

// 可惜了，想了有一天二进制，结果是六进制的做法

using namespace std;

struct Door {
    int r1, c1, r2, c2;
};

vector<Door> locked_doors;


void lock_right(int r, int c) {
    if (r >= 1 && r <= 50 && c >= 1 && c + 1 <= 50) {
        locked_doors.push_back({r, c, r, c + 1});
    }
}

void lock_down(int r, int c) {
    if (r >= 1 && r + 1 <= 50 && c >= 1 && c <= 50) {
        locked_doors.push_back({r, c, r + 1, c});
    }
}

int main() {
    // 提升 IO 效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long T;
    if (!(cin >> T)) return 0;
    
    // 1. 构建上方收集通道的外墙 (j = 0 到 22，第 23 个模块直接流入网格边界)
    for (int j = 0; j <= 22; ++j) {
        lock_right(2 * j + 1, 2 * j + 4);
        lock_down(2 * j + 2, 2 * j + 4);
        lock_down(2 * j + 2, 2 * j + 5);
        lock_right(2 * j + 2, 2 * j + 6);
    }
    
    // 2. 构建下方收集通道的外墙 (j = 0 到 22)
    for (int j = 0; j <= 22; ++j) {
        lock_down(2 * j + 4, 2 * j + 1);
        lock_right(2 * j + 4, 2 * j + 2);
        lock_right(2 * j + 5, 2 * j + 2);
        lock_down(2 * j + 6, 2 * j + 2);
    }
    
    // 3. 处理六进制位并设置提取门
    for (int j = 0; j <= 23; ++j) {
        int d = T % 6; // 当前位的需求量 (0-5)
        T /= 6;
        
        bool u1 = true, u3 = true, l1 = true, l3 = true; // true 代表门要锁死
        
        // 用 1, 1, 3, 3 拼凑出 0-5 的任意数字
        if (d == 1) { u1 = false; }
        else if (d == 2) { u1 = false; l1 = false; }
        else if (d == 3) { u3 = false; }
        else if (d == 4) { u3 = false; u1 = false; }
        else if (d == 5) { u3 = false; u1 = false; l1 = false; }
        
        // 如果布尔值为 true，说明不需要提取该权重的路径，用锁封死
        if (u1) lock_right(2 * j + 1, 2 * j + 3); // 上方权重 1
        if (u3) lock_right(2 * j + 2, 2 * j + 3); // 上方权重 3
        if (l1) lock_down(2 * j + 3, 2 * j + 1);  // 下方权重 1
        if (l3) lock_down(2 * j + 3, 2 * j + 2);  // 下方权重 3
    }
    
    // 4. 封死主干道的末端点，防止未被提取的巨量冗余路径溢出到终点
    lock_right(49, 49);
    lock_down(49, 49);
    
    // 输出结果
    cout << 50 << " " << 50 << "\n";
    cout << locked_doors.size() << "\n";
    for (const auto& door : locked_doors) {
        cout << door.r1 << " " << door.c1 << " " << door.r2 << " " << door.c2 << "\n";
    }
    
    return 0;
}