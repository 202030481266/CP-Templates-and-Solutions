#include <iostream>
#include <vector>
#include <cstring> // 用于memset

const int MAXN = 1e5 + 5; // 最大节点数
const int MAXM = 2e5 + 5; // 最大边数

struct Edge {
    int to;   // 边的终点
    int w;    // 边的权值
    int next; // 与该边同起点的下一条边的编号
};

Edge edge[MAXM]; // 存储所有边的信息
int head[MAXN];  // head[i]表示以i为起点的第一条边的编号
int cnt;         // 当前边的总数

// 初始化图
void init() {
    memset(head, -1, sizeof(head)); // 将所有head初始化为-1，表示没有边
    cnt = 0; // 边计数器初始化为0
}

// 添加一条从from到to，权值为weight的有向边
void addEdge(int from, int to, int weight) {
    edge[cnt].to = to;
    edge[cnt].w = weight;
    edge[cnt].next = head[from]; // 将新边的next指向原来的第一条边
    head[from] = cnt++; // 更新head[from]为新边的编号
}

// 添加一条无向边（相当于添加两条方向相反的有向边）
void addBidirectionalEdge(int u, int v, int weight) {
    addEdge(u, v, weight);
    addEdge(v, u, weight);
}

// 遍历从u出发的所有边
void traverse(int u) {
    std::cout << "从节点 " << u << " 出发的所有边：" << std::endl;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        int w = edge[i].w;
        std::cout << "到达节点 " << v << "，权值为 " << w << std::endl;
    }
}

// 深度优先搜索
bool visited[MAXN];

void dfs(int u) {
    visited[u] = true;
    std::cout << "访问节点：" << u << std::endl;
    
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    init(); // 初始化图
    
    // 构建一个示例图
    addBidirectionalEdge(1, 2, 5);
    addBidirectionalEdge(1, 3, 3);
    addBidirectionalEdge(2, 3, 1);
    addBidirectionalEdge(2, 4, 6);
    addBidirectionalEdge(3, 4, 2);
    
    // 遍历从节点1出发的所有边
    traverse(1);
    
    // 从节点1开始深度优先搜索
    std::cout << "\n从节点1开始DFS：" << std::endl;
    memset(visited, false, sizeof(visited));
    dfs(1);
    
    return 0;
}