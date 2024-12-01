#include <iostream>
#include <algorithm>
#include <cstring>
#include <random>
#include <climits>

using namespace std;

class Treap {
private:
    static const int MAXN = 100001;
    int cnt, head;
    int key[MAXN];
    int key_count[MAXN];
    int ls[MAXN];
    int rs[MAXN];
    int tree_size[MAXN];
    double priority[MAXN];

    // Update size of node
    void updateSize(int i) {
        tree_size[i] = tree_size[ls[i]] + tree_size[rs[i]] + key_count[i];
    }

    // Left rotation
    int leftRotate(int i) {
        int r = rs[i];
        rs[i] = ls[r];
        ls[r] = i;
        updateSize(i);
        updateSize(r);
        return r;
    }

    // Right rotation
    int rightRotate(int i) {
        int l = ls[i];
        ls[i] = rs[l];
        rs[l] = i;
        updateSize(i);
        updateSize(l);
        return l;
    }

    // Internal add function
    int addNode(int i, int num) {
        if (i == 0) {
            key[++cnt] = num;
            key_count[cnt] = tree_size[cnt] = 1;
            priority[cnt] = static_cast<double>(rand()) / RAND_MAX;
            return cnt;
        }
        
        if (key[i] == num) {
            key_count[i]++;
        } else if (key[i] > num) {
            ls[i] = addNode(ls[i], num);
            if (ls[i] != 0 && priority[ls[i]] > priority[i]) {
                return rightRotate(i);
            }
        } else {
            rs[i] = addNode(rs[i], num);
            if (rs[i] != 0 && priority[rs[i]] > priority[i]) {
                return leftRotate(i);
            }
        }
        
        updateSize(i);
        return i;
    }

    // Count numbers smaller than num
    int countSmaller(int i, int num) {
        if (i == 0) return 0;
        
        if (key[i] >= num) {
            return countSmaller(ls[i], num);
        }
        return tree_size[ls[i]] + key_count[i] + countSmaller(rs[i], num);
    }

    // Internal getIndex function
    int getNodeByRank(int i, int x) {
        if (tree_size[ls[i]] >= x) {
            return getNodeByRank(ls[i], x);
        }
        if (tree_size[ls[i]] + key_count[i] < x) {
            return getNodeByRank(rs[i], x - tree_size[ls[i]] - key_count[i]);
        }
        return key[i];
    }

    // Internal predecessor function
    int findPre(int i, int num) {
        if (i == 0) return INT_MIN;
        
        if (key[i] >= num) {
            return findPre(ls[i], num);
        }
        return max(key[i], findPre(rs[i], num));
    }

    // Internal successor function
    int findPost(int i, int num) {
        if (i == 0) return INT_MAX;
        
        if (key[i] <= num) {
            return findPost(rs[i], num);
        }
        return min(key[i], findPost(ls[i], num));
    }

    // Internal remove function
    int removeNode(int i, int num) {
        if (i == 0) return 0;
        
        if (key[i] < num) {
            rs[i] = removeNode(rs[i], num);
        } else if (key[i] > num) {
            ls[i] = removeNode(ls[i], num);
        } else {
            if (key_count[i] > 1) {
                key_count[i]--;
            } else {
                if (ls[i] == 0) return rs[i];
                if (rs[i] == 0) return ls[i];
                
                if (priority[ls[i]] >= priority[rs[i]]) {
                    i = rightRotate(i);
                    rs[i] = removeNode(rs[i], num);
                } else {
                    i = leftRotate(i);
                    ls[i] = removeNode(ls[i], num);
                }
            }
        }
        
        updateSize(i);
        return i;
    }

public:
    Treap() : cnt(0), head(0) {}

    void add(int num) {
        head = addNode(head, num);
    }

    void remove(int num) {
        if (getRank(num) != getRank(num + 1)) {
            head = removeNode(head, num);
        }
    }

    int getRank(int num) {
        return countSmaller(head, num) + 1;
    }

    int getByRank(int x) {
        return getNodeByRank(head, x);
    }

    int getPre(int num) {
        return findPre(head, num);
    }

    int getPost(int num) {
        return findPost(head, num);
    }

    void clear() {
        fill(key + 1, key + cnt + 1, 0);
        fill(key_count + 1, key_count + cnt + 1, 0);
        fill(ls + 1, ls + cnt + 1, 0);
        fill(rs + 1, rs + cnt + 1, 0);
        fill(tree_size + 1, tree_size + cnt + 1, 0);
        fill(priority + 1, priority + cnt + 1, 0);
        cnt = 0;
        head = 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    srand(time(0));
    Treap treap;
    int n;
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        int op, x;
        cin >> op >> x;
        switch (op) {
            case 1: treap.add(x); break;
            case 2: treap.remove(x); break;
            case 3: cout << treap.getRank(x) << '\n'; break;
            case 4: cout << treap.getByRank(x) << '\n'; break;
            case 5: cout << treap.getPre(x) << '\n'; break;
            case 6: cout << treap.getPost(x) << '\n'; break;
        }
    }
    
    return 0;
}