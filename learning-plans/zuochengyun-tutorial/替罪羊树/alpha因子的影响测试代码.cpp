#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class ScapegoatTree {
private:
    static const int MAXN = 100001;
    double ALPHA = 0.7;
    int max_num;
    int cost;
    
    int head = 0;
    int cnt = 0;
    vector<int> key;
    vector<int> count;
    vector<int> left;
    vector<int> right;
    vector<int> size;
    vector<int> diff;
    vector<int> collect;
    
    int ci;
    int top;
    int father;
    int side;
    
    int init(int num) {
        ++cnt;
        key[cnt] = num;
        left[cnt] = right[cnt] = 0;
        count[cnt] = size[cnt] = diff[cnt] = 1;
        return cnt;
    }
    
    void up(int i) {
        size[i] = size[left[i]] + size[right[i]] + count[i];
        diff[i] = diff[left[i]] + diff[right[i]] + (count[i] > 0 ? 1 : 0);
    }
    
    void inorder(int i) {
        if (i != 0) {
            inorder(left[i]);
            if (count[i] > 0) {
                collect[++ci] = i;
            }
            inorder(right[i]);
        }
    }
    
    int build(int l, int r) {
        if (l > r) return 0;
        int m = (l + r) / 2;
        int h = collect[m];
        left[h] = build(l, m - 1);
        right[h] = build(m + 1, r);
        up(h);
        return h;
    }
    
    void rebuild() {
        if (top != 0) {
            ci = 0;
            inorder(top);
            if (ci > 0) {
                cost += ci; // 统计重构节点数
                if (father == 0) {
                    head = build(1, ci);
                } else if (side == 1) {
                    left[father] = build(1, ci);
                } else {
                    right[father] = build(1, ci);
                }
            }
        }
    }
    
    bool balance(int i) {
        return ALPHA * diff[i] >= max(diff[left[i]], diff[right[i]]);
    }
    
    void add(int i, int f, int s, int num) {
        if (i == 0) {
            if (f == 0) {
                head = init(num);
            } else if (s == 1) {
                left[f] = init(num);
            } else {
                right[f] = init(num);
            }
        } else {
            if (key[i] == num) {
                count[i]++;
            } else if (key[i] > num) {
                add(left[i], i, 1, num);
            } else {
                add(right[i], i, 2, num);
            }
            up(i);
            if (!balance(i)) {
                top = i;
                father = f;
                side = s;
            }
        }
    }
    
    int small(int i, int num) {
        if (i == 0) return 0;
        if (key[i] >= num) {
            return small(left[i], num);
        } else {
            return size[left[i]] + count[i] + small(right[i], num);
        }
    }
    
    int index(int i, int x) {
        if (size[left[i]] >= x) {
            return index(left[i], x);
        } else if (size[left[i]] + count[i] < x) {
            return index(right[i], x - size[left[i]] - count[i]);
        }
        return key[i];
    }
    
    void remove(int i, int f, int s, int num) {
        if (key[i] == num) {
            count[i]--;
        } else if (key[i] > num) {
            remove(left[i], i, 1, num);
        } else {
            remove(right[i], i, 2, num);
        }
        up(i);
        if (!balance(i)) {
            top = i;
            father = f;
            side = s;
        }
    }
    
    int deep(int i) {
        if (i == 0) return 0;
        return max(deep(left[i]), deep(right[i])) + 1;
    }

public:
    ScapegoatTree(double alpha = 0.7) : ALPHA(alpha) {
        key.resize(MAXN);
        count.resize(MAXN);
        left.resize(MAXN);
        right.resize(MAXN);
        size.resize(MAXN);
        diff.resize(MAXN);
        collect.resize(MAXN);
        clear();
    }
    
    void add(int num) {
        top = father = side = 0;
        add(head, 0, 0, num);
        rebuild();
    }
    
    int rank(int num) {
        return small(head, num) + 1;
    }
    
    int get_index(int x) {
        return index(head, x);
    }
    
    int pre(int num) {
        int kth = rank(num);
        if (kth == 1) {
            return INT_MIN;
        } else {
            return get_index(kth - 1);
        }
    }
    
    int post(int num) {
        int kth = rank(num + 1);
        if (kth == size[head] + 1) {
            return INT_MAX;
        } else {
            return get_index(kth);
        }
    }
    
    void remove(int num) {
        if (rank(num) != rank(num + 1)) {
            top = father = side = 0;
            remove(head, 0, 0, num);
            rebuild();
        }
    }
    
    void clear() {
        fill(key.begin() + 1, key.begin() + cnt + 1, 0);
        fill(count.begin() + 1, count.begin() + cnt + 1, 0);
        fill(left.begin() + 1, left.begin() + cnt + 1, 0);
        fill(right.begin() + 1, right.begin() + cnt + 1, 0);
        fill(size.begin() + 1, size.begin() + cnt + 1, 0);
        fill(diff.begin() + 1, diff.begin() + cnt + 1, 0);
        cnt = 0;
        head = 0;
        cost = 0;
    }
    
    int get_height() {
        return deep(head);
    }
    
    int get_cost() {
        return cost;
    }
};

int main() {
    const int max_num = 10000;  // 设置插入范围
    double alpha = 0.7;         // 设置平衡因子
    
    cout << "测试开始" << endl;
    ScapegoatTree tree(alpha);
    
    for (int num = 1; num <= max_num; num++) {
        tree.add(num);
    }
    
    cout << "插入数字 : 1~" << max_num << endl;
    cout << "平衡因子 : " << alpha << endl;
    cout << "树的高度 : " << tree.get_height() << endl;
    cout << "重构节点 : " << tree.get_cost() << endl;
    cout << "测试结束" << endl;
    
    return 0;
}