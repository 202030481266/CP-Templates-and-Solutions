// 替罪羊树的实现(C++版)
// 实现一种结构，支持如下操作，要求单次调用的时间复杂度O(log n)
// 1，增加x，重复加入算多个词频
// 2，删除x，如果有多个，只删掉一个
// 3，查询x的排名，x的排名为，比x小的数的个数+1
// 4，查询数据中排名为x的数
// 5，查询x的前驱，x的前驱为，小于x的数中最大的数，不存在返回整数最小值
// 6，查询x的后继，x的后继为，大于x的数中最小的数，不存在返回整数最大值
// 所有操作的次数 <= 10^5
// -10^7 <= x <= +10^7
// 测试链接 : https://www.luogu.com.cn/problem/P3369
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cstring>

using namespace std;

/**
 * @brief Scapegoat Tree Implementation
 * A self-balancing binary search tree that maintains balance using the alpha-height property
 */
class ScapegoatTree {
private:
    // Constants
    static constexpr double ALPHA = 0.7;  // Balance factor
    static constexpr int MAXN = 100001;   // Maximum number of nodes

    // Tree node properties
    int head = 0;      // Root of the tree
    int cnt = 0;       // Total number of nodes
    
    // Node arrays
    int key[MAXN];         // Node values
    int key_count[MAXN];   // Count of each key (allows duplicates)
    int ls[MAXN];         // Left child pointers
    int rs[MAXN];         // Right child pointers
    int size[MAXN];       // Subtree sizes
    int diff[MAXN];       // Number of different values in subtree
    
    // Rebuild helper variables
    int collect[MAXN];    // Temporary array for rebuilding
    int ci;               // Collect array index
    int top;              // Top node for rebuilding
    int father;           // Parent of the rebuild subtree
    int side;            // Side of parent (1 for left, 2 for right)

    /**
     * @brief Initialize a new node
     * @param num Value to store in the node
     * @return Index of the new node
     */
    int init(int num) {
        key[++cnt] = num;
        ls[cnt] = rs[cnt] = 0;
        key_count[cnt] = size[cnt] = diff[cnt] = 1;
        return cnt;
    }

    /**
     * @brief Update node statistics (size and diff)
     * @param i Node index
     */
    void up(int i) {
        size[i] = size[ls[i]] + size[rs[i]] + key_count[i];
        diff[i] = diff[ls[i]] + diff[rs[i]] + (key_count[i] > 0 ? 1 : 0);
    }

    /**
     * @brief Perform inorder traversal to collect nodes
     * @param i Current node index
     */
    void inorder(int i) {
        if (i != 0) {
            inorder(ls[i]);
            if (key_count[i] > 0) {
                collect[++ci] = i;
            }
            inorder(rs[i]);
        }
    }

    /**
     * @brief Build a balanced tree from collected nodes
     * @param l Left bound
     * @param r Right bound
     * @return Root of the built subtree
     */
    int build(int l, int r) {
        if (l > r) return 0;
        
        int m = (l + r) / 2;
        int h = collect[m];
        ls[h] = build(l, m - 1);
        rs[h] = build(m + 1, r);
        up(h);
        return h;
    }

    /**
     * @brief Rebuild the tree to maintain balance
     */
    void rebuild() {
        if (top != 0) {
            ci = 0;
            inorder(top);
            if (ci > 0) {
                int newRoot = build(1, ci);
                if (father == 0) {
                    head = newRoot;
                } else if (side == 1) {
                    ls[father] = newRoot;
                } else {
                    rs[father] = newRoot;
                }
            }
        }
    }

    /**
     * @brief Check if a subtree maintains the alpha balance property
     * @param i Root of subtree
     * @return true if balanced, false otherwise
     */
    bool balance(int i) {
        return ALPHA * diff[i] >= max(diff[ls[i]], diff[rs[i]]);
    }

    /**
     * @brief Helper function for add operation
     */
    void add(int i, int f, int s, int num) {
        if (i == 0) {
            if (f == 0) head = init(num);
            else if (s == 1) ls[f] = init(num);
            else rs[f] = init(num);
        } else {
            if (key[i] == num) {
                key_count[i]++;
            } else if (key[i] > num) {
                add(ls[i], i, 1, num);
            } else {
                add(rs[i], i, 2, num);
            }
            up(i);
            if (!balance(i)) {
                top = i;
                father = f;
                side = s;
            }
        }
    }

    /**
     * @brief Helper function for remove operation
     */
    void remove(int i, int f, int s, int num) {
        if (key[i] == num) {
            key_count[i]--;
        } else if (key[i] > num) {
            remove(ls[i], i, 1, num);
        } else {
            remove(rs[i], i, 2, num);
        }
        up(i);
        if (!balance(i)) {
            top = i;
            father = f;
            side = s;
        }
    }

public:
    /**
     * @brief Add a number to the tree
     * @param num Number to add
     */
    void add(int num) {
        top = father = side = 0;
        add(head, 0, 0, num);
        rebuild();
    }

    /**
     * @brief Remove a number from the tree
     * @param num Number to remove
     */
    void remove(int num) {
        if (getRank(num) != getRank(num + 1)) {
            top = father = side = 0;
            remove(head, 0, 0, num);
            rebuild();
        }
    }

    /**
     * @brief Get the rank of a number in the tree
     * @param num Number to query
     * @return Rank of the number
     */
    int getRank(int num) {
        return small(head, num) + 1;
    }

    /**
     * @brief Get the number at a given rank
     * @param x Rank to query
     * @return Number at the given rank
     */
    int index(int x) {
        return index(head, x);
    }

    /**
     * @brief Get the predecessor of a number
     * @param num Number to query
     * @return Predecessor of the number
     */
    int pre(int num) {
        int kth = getRank(num);
        if (kth == 1) return INT_MIN;
        return index(kth - 1);
    }

    /**
     * @brief Get the successor of a number
     * @param num Number to query
     * @return Successor of the number
     */
    int post(int num) {
        int kth = getRank(num + 1);
        if (kth == size[head] + 1) return INT_MAX;
        return index(kth);
    }

    /**
     * @brief Clear the tree
     */
    void clear() {
        memset(key, 0, sizeof(key));
        memset(key_count, 0, sizeof(key_count));
        memset(ls, 0, sizeof(ls));
        memset(rs, 0, sizeof(rs));
        memset(size, 0, sizeof(size));
        memset(diff, 0, sizeof(diff));
        cnt = 0;
        head = 0;
    }

private:
    /**
     * @brief Helper function to count smaller elements
     */
    int small(int i, int num) {
        if (i == 0) return 0;
        if (key[i] >= num) {
            return small(ls[i], num);
        } else {
            return size[ls[i]] + key_count[i] + small(rs[i], num);
        }
    }

    /**
     * @brief Helper function for index operation
     */
    int index(int i, int x) {
        if (size[ls[i]] >= x) {
            return index(ls[i], x);
        } else if (size[ls[i]] + key_count[i] < x) {
            return index(rs[i], x - size[ls[i]] - key_count[i]);
        }
        return key[i];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ScapegoatTree tree;
    int n;
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        int op, x;
        cin >> op >> x;
        
        switch (op) {
            case 1: tree.add(x); break;
            case 2: tree.remove(x); break;
            case 3: cout << tree.getRank(x) << "\n"; break;
            case 4: cout << tree.index(x) << "\n"; break;
            case 5: cout << tree.pre(x) << "\n"; break;
            case 6: cout << tree.post(x) << "\n"; break;
        }
    }
    
    return 0;
}