#include <bits/stdc++.h>
using namespace std;

// 假设 GridMaster 接口已定义如下：
// class GridMaster {
// public:
//     bool canMove(char direction); // 'U', 'D', 'L', 'R'
//     int move(char direction); // 返回移动后的消耗值，-1 表示无法移动
//     bool isTarget();
// };

// 解决方案类
class Solution {
public:
    // 定义方向和对应的反方向
    vector<char> dirs = {'U', 'D', 'L', 'R'};
    vector<char> revDirs = {'D', 'U', 'R', 'L'};
    vector<pair<int, int>> moveOffsets = { {-1,0}, {1,0}, {0,-1}, {0,1} };

    // 偏移量，用于将坐标映射到数组索引
    static const int OFFSET = 100;
    // 假设网格最大为201x201
    int gridSize = 201;
    // 存储网格的消耗值，-1 表示不可达或未探索
    vector<vector<int>> grid;
    // 记录是否已访问
    vector<vector<bool>> visitedGrid;
    // 目标坐标
    pair<int, int> targetPos = {-1, -1};

    // 主函数
    int findShortestPath(GridMaster& master) {
        // 初始化网格
        grid = vector<vector<int>>(gridSize, vector<int>(gridSize, -1));
        visitedGrid = vector<vector<bool>>(gridSize, vector<bool>(gridSize, false));

        // 开始DFS探索，起始坐标为(0,0)
        dfs(master, 0, 0);

        // 如果未找到目标，返回-1
        if (targetPos.first == -1 && targetPos.second == -1) {
            return -1;
        }

        // 运行Dijkstra算法找到最小总消耗
        return dijkstra();
    }

private:
    // DFS探索函数
    void dfs(GridMaster& master, int x, int y) {
        // 映射坐标
        int mappedX = x + OFFSET;
        int mappedY = y + OFFSET;

        // 标记为已访问
        visitedGrid[mappedX][mappedY] = true;

        // 检查是否为目标
        if (master.isTarget()) {
            targetPos = {x, y};
        }

        // 遍历四个方向
        for (int i = 0; i < 4; ++i) {
            char dir = dirs[i];
            char revDir = revDirs[i];
            int newX = x + moveOffsets[i].first;
            int newY = y + moveOffsets[i].second;
            int mappedNewX = newX + OFFSET;
            int mappedNewY = newY + OFFSET;

            // 如果该方向可以移动且未被访问
            if (master.canMove(dir) && !visitedGrid[mappedNewX][mappedNewY]) {
                // 移动到新单元格
                int cost = master.move(dir);
                if (cost != -1) {
                    // 记录消耗值
                    grid[mappedNewX][mappedNewY] = cost;
                    // 递归探索新单元格
                    dfs(master, newX, newY);
                    // 回溯到当前单元格
                    master.move(revDir);
                }
            }
        }
    }

    // Dijkstra算法函数
    int dijkstra() {
        // 映射起始和目标坐标
        int startX = OFFSET;
        int startY = OFFSET;
        int endX = targetPos.first + OFFSET;
        int endY = targetPos.second + OFFSET;

        // 定义优先队列，存储 {当前消耗, x, y}
        // 使用小顶堆
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, std::greater<tuple<int, int, int>>> pq;
        pq.emplace(0, startX, startY);

        // 定义距离数组，初始化为无穷大
        vector<vector<int>> dist(gridSize, vector<int>(gridSize, INT32_MAX));
        dist[startX][startY] = 0;

        // 定义四个移动方向
        vector<pair<int, int>> directions = { {-1,0}, {1,0}, {0,-1}, {0,1} };

        while (!pq.empty()) {
            auto [currentCost, x, y] = pq.top(); pq.pop();

            // 如果到达目标，返回当前消耗
            if (x == endX && y == endY) {
                return currentCost;
            }

            // 遍历四个方向
            for (auto &[dx, dy] : directions) {
                int newX = x + dx;
                int newY = y + dy;

                // 检查边界和可达性
                if (newX >= 0 && newX < gridSize && newY >= 0 && newY < gridSize && grid[newX][newY] != -1) {
                    int newCost = currentCost + grid[newX][newY];
                    if (newCost < dist[newX][newY]) {
                        dist[newX][newY] = newCost;
                        pq.emplace(newCost, newX, newY);
                    }
                }
            }
        }

        // 如果目标不可达，返回-1
        return -1;
    }
};
