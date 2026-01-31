// https://www.luogu.com.cn/problem/P4169
// KD树跑的飞快
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 600010;
const int INF = 0x3f3f3f3f;
const double ALPHA = 0.725;  // KD树平衡因子

// 全局变量
int operation, n, m, queryX, queryY, nodeCount, stackTop, root, minDistance;
int subtreeSize[MAXN], splitDimension[MAXN], leftChild[MAXN], rightChild[MAXN], nodeStack[MAXN];
int minX[MAXN], maxX[MAXN], minY[MAXN], maxY[MAXN];

struct Point {
    int x, y;
} points[MAXN];

// 比较函数
inline bool compareByX(int a, int b) { return points[a].x < points[b].x; }
inline bool compareByY(int a, int b) { return points[a].y < points[b].y; }

// 检查节点是否需要重构
inline bool needRebuild(int node) {
    return ALPHA * subtreeSize[node] <= (double)max(subtreeSize[leftChild[node]], subtreeSize[rightChild[node]]);
}

// 中序遍历收集节点
void collectNodes(int node) {
    if (!node) return;
    collectNodes(leftChild[node]);
    nodeStack[++stackTop] = node;
    collectNodes(rightChild[node]);
}

// 更新节点信息
void updateNode(int node) {
    int left = leftChild[node], right = rightChild[node];
    subtreeSize[node] = subtreeSize[left] + subtreeSize[right] + 1;
    
    // 初始化边界
    minX[node] = maxX[node] = points[node].x;
    minY[node] = maxY[node] = points[node].y;
    
    // 更新左子树边界
    if (left) {
        minX[node] = min(minX[node], minX[left]);
        maxX[node] = max(maxX[node], maxX[left]);
        minY[node] = min(minY[node], minY[left]);
        maxY[node] = max(maxY[node], maxY[left]);
    }
    
    // 更新右子树边界
    if (right) {
        minX[node] = min(minX[node], minX[right]);
        maxX[node] = max(maxX[node], maxX[right]);
        minY[node] = min(minY[node], minY[right]);
        maxY[node] = max(maxY[node], maxY[right]);
    }
}

// 构建KD树
int buildKDTree(int left, int right) {
    if (left > right) return 0;
    
    int mid = (left + right) >> 1;
    double avgX = 0, avgY = 0, varX = 0, varY = 0;
    
    // 计算平均值
    for (int i = left; i <= right; i++) {
        avgX += points[nodeStack[i]].x;
        avgY += points[nodeStack[i]].y;
    }
    avgX /= (right - left + 1);
    avgY /= (right - left + 1);
    
    // 计算方差
    for (int i = left; i <= right; i++) {
        double dx = points[nodeStack[i]].x - avgX;
        double dy = points[nodeStack[i]].y - avgY;
        varX += dx * dx;
        varY += dy * dy;
    }
    
    // 选择分割维度
    if (varX > varY) {
        nth_element(nodeStack + left, nodeStack + mid, nodeStack + right + 1, compareByX);
        splitDimension[nodeStack[mid]] = 1;  // 按x分割
    } else {
        nth_element(nodeStack + left, nodeStack + mid, nodeStack + right + 1, compareByY);
        splitDimension[nodeStack[mid]] = 2;  // 按y分割
    }
    
    leftChild[nodeStack[mid]] = buildKDTree(left, mid - 1);
    rightChild[nodeStack[mid]] = buildKDTree(mid + 1, right);
    updateNode(nodeStack[mid]);
    
    return nodeStack[mid];
}

// 重构子树
void rebuildSubtree(int &node) {
    stackTop = 0;
    collectNodes(node);
    node = buildKDTree(1, stackTop);
}

// 插入节点
void insertNode(int &node, int newNode) {
    if (!node) {
        node = newNode;
        updateNode(node);
        return;
    }
    
    if (splitDimension[node] == 1) {
        if (points[newNode].x <= points[node].x) {
            insertNode(leftChild[node], newNode);
        } else {
            insertNode(rightChild[node], newNode);
        }
    } else {
        if (points[newNode].y <= points[node].y) {
            insertNode(leftChild[node], newNode);
        } else {
            insertNode(rightChild[node], newNode);
        }
    }
    
    updateNode(node);
    if (needRebuild(node)) {
        rebuildSubtree(node);
    }
}

// 计算点到矩形的最小距离
inline int calculateDistance(int node) {
    return max(0, minX[node] - queryX) + max(0, queryX - maxX[node]) +
           max(0, minY[node] - queryY) + max(0, queryY - maxY[node]);
}

// 查询最近点
void queryNearest(int node) {
    if (!node) return;
    
    int currentDistance = abs(points[node].x - queryX) + abs(points[node].y - queryY);
    if (currentDistance < minDistance) {
        minDistance = currentDistance;
    }
    
    int leftDistance = INF, rightDistance = INF;
    if (leftChild[node]) leftDistance = calculateDistance(leftChild[node]);
    if (rightChild[node]) rightDistance = calculateDistance(rightChild[node]);
    
    // 优先搜索距离更近的子树
    if (leftDistance < rightDistance) {
        if (leftDistance < minDistance) queryNearest(leftChild[node]);
        if (rightDistance < minDistance) queryNearest(rightChild[node]);
    } else {
        if (rightDistance < minDistance) queryNearest(rightChild[node]);
        if (leftDistance < minDistance) queryNearest(leftChild[node]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    scanf("%d%d", &n, &m);
    
    // 初始化点
    for (int i = 1; i <= n; i++) {
        nodeCount++;
        scanf("%d%d", &points[nodeCount].x, &points[nodeCount].y);
        insertNode(root, nodeCount);
    }
    
    // 处理操作
    while (m--) {
        scanf("%d", &operation);
        if (operation == 1) {
            // 插入新点
            nodeCount++;
            scanf("%d%d", &points[nodeCount].x, &points[nodeCount].y);
            insertNode(root, nodeCount);
        } else {
            // 查询最近点
            scanf("%d%d", &queryX, &queryY);
            minDistance = INF;
            queryNearest(root);
            printf("%d\n", minDistance);
        }
    }
    
    return 0;
}