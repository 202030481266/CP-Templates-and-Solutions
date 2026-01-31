#include <iostream>
#include <vector>
#include <random>
#include <chrono>

// 使用 mt19937 提供高质量随机数
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int val;      // 节点值
    int pri;      // 随机优先级
    int size;     // 子树大小
    int ch[2];    // 左右孩子指针 (0: 左, 1: 右)

    Node(int v = 0) : val(v), pri(rng()), size(1), ch{ 0, 0 } {}
};

const int MAXN = 100005; // 视题目数据范围调整
Node tree[MAXN];
int tot = 0; // 当前节点总数，也用作新节点索引
int root = 0; // 树根

// 更新节点 u 的 size 信息
void pushUp(int u) {
    if (u) {
        tree[u].size = tree[tree[u].ch[0]].size + tree[tree[u].ch[1]].size + 1;
    }
}

// 创建一个新节点
int newNode(int val) {
    tree[++tot] = Node(val);
    return tot;
}

// 合并 x 和 y 两棵树，返回新根。(要求 x 中所有值 < y 中所有值)
int merge(int x, int y) {
    if (!x || !y) return x + y; // 如果有一个为空，返回另一个
    if (tree[x].pri > tree[y].pri) { // x 优先级高，x作根
        tree[x].ch[1] = merge(tree[x].ch[1], y); // 递归合并 x 的右子树和 y
        pushUp(x);
        return x;
    }
    else { // y 优先级高，y作根
        tree[y].ch[0] = merge(x, tree[y].ch[0]); // 递归合并 x 和 y 的左子树
        pushUp(y);
        return y;
    }
}

// 按值 k 分裂树 u，结果存入 x (<= k) 和 y (> k)
// 注意 x 和 y 是传引用，会被修改
void split(int u, int k, int& x, int& y) {
    if (!u) {
        x = y = 0; // 空树分裂结果是两个空树
        return;
    }
    if (tree[u].val <= k) { // 当前节点值 <= k，归入 x 树
        x = u; // u 作为 x 的根
        split(tree[u].ch[1], k, tree[u].ch[1], y); // 递归分裂 u 的右子树
    }
    else { // 当前节点值 > k，归入 y 树
        y = u; // u 作为 y 的根
        split(tree[u].ch[0], k, x, tree[u].ch[0]); // 递归分裂 u 的左子树
    }
    pushUp(u); // 分裂后更新 size
}

// 插入值 val
void insert(int val) {
    int x, y;
    split(root, val, x, y); // 按 val 分裂
    root = merge(merge(x, newNode(val)), y); // 合并 x, 新节点, y
}

// 删除值 val (只删除一个)
void erase(int val) {
    int x, y, z;
    split(root, val, x, z);       // 分裂出 <= val (x) 和 > val (z)
    split(x, val - 1, x, y);      // 从 x 中分裂出 < val (x) 和 == val (y)
    if (y) { // 如果找到了值为 val 的节点 (y 非空)
        y = merge(tree[y].ch[0], tree[y].ch[1]); // 合并 y 的左右子树，丢弃根
    }
    root = merge(merge(x, y), z); // 重新合并三部分
}

// 查询值 val 的排名 (定义为 < val 的数的个数 + 1)
int getRankByVal(int val) {
    int x, y;
    split(root, val - 1, x, y); // 分裂出 < val (x) 和 >= val (y)
    int rank = tree[x].size + 1; // x 的大小即为 < val 的数的个数
    root = merge(x, y);        // 合并回去，恢复树
    return rank;
}

// 查询排名为 k 的值 (k 从 1 开始)
int getValByRank(int k) {
    int u = root;
    while (u) {
        int leftSize = tree[tree[u].ch[0]].size;
        if (leftSize + 1 == k) { // 刚好是当前节点
            return tree[u].val;
        }
        else if (leftSize >= k) { // 在左子树
            u = tree[u].ch[0];
        }
        else { // 在右子树
            k -= (leftSize + 1);
            u = tree[u].ch[1];
        }
    }
    return -1; // 排名 k 超出范围或树为空
}

// 查找值 val 的前驱 (小于 val 的最大值)
int getPrev(int val) {
    int x, y;
    split(root, val - 1, x, y); // 分裂出 < val (x) 和 >= val (y)
    if (!x) return -1; // 没有比 val 小的数
    // 为了在 x 中找到最后一个，我们暂时让 x 成为根来查询
    int current_root = root;
    root = x;
    int res = getValByRank(tree[x].size); // x 中的最大值即为排名为 size[x] 的值
    root = current_root;
    root = merge(x, y); // 合并回去
    return res;
}

// 查找值 val 的后继 (大于 val 的最小值)
int getNext(int val) {
    int x, y;
    split(root, val, x, y); // 分裂出 <= val (x) 和 > val (y)
    if (!y) return -1; // 没有比 val 大的数
    // 为了在 y 中找第 1，我们暂时让 y 成为根来查询
    int current_root = root; // 保存原来的根
    root = y; // 临时设置 y 为根
    int res = getValByRank(1);
    root = current_root; // 恢复原来的根状态 (虽然merge会重建)
    root = merge(x, y); // 合并回去
    return res;

    /* 更安全的 getNext 实现方式:
    int getNext(int val) {
        int x, y;
        split(root, val, x, y); // x <= val, y > val
        if (!y) {
            root = merge(x, y); // Merge back before returning
            return -1; // No successor
        }
        int u = y;
        while (tree[u].ch[0]) { // Find the leftmost node in y
            u = tree[u].ch[0];
        }
        int res = tree[u].val;
        root = merge(x, y); // Merge back
        return res;
    }
    */
}

// 主函数示例
int main() {
    // 初始化，防止访问 tree[0] 的 size 等属性
    tree[0].size = 0;
    tree[0].pri = -1; // 优先级最低

    insert(10);
    insert(20);
    insert(5);
    insert(15);
    insert(25);

    std::cout << "Rank of 15: " << getRankByVal(15) << std::endl; // 应输出 3
    std::cout << "Value at rank 4: " << getValByRank(4) << std::endl; // 应输出 20

    std::cout << "Prev of 20: " << getPrev(20) << std::endl; // 应输出 15
    std::cout << "Next of 10: " << getNext(10) << std::endl; // 应输出 15

    erase(15);
    std::cout << "After erasing 15, Rank of 20: " << getRankByVal(20) << std::endl; // 应输出 3
    std::cout << "After erasing 15, Value at rank 3: " << getValByRank(3) << std::endl; // 应输出 20

    return 0;
}