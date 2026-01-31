#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int val, pri, size, ch[2];
    Node(int v = 0) : val(v), pri(rng()), size(1), ch{ 0, 0 } {}
};

const int MAXN = 100005;
Node tree[MAXN];
int tot, root;

void pushUp(int u) {
    if (u) {
        tree[u].size = tree[tree[u].ch[0]].size + tree[tree[u].ch[1]].size + 1;
    }
}
int newNode(int val) {
    tree[++tot] = Node(val);
    return tot;
}
int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (tree[x].pri > tree[y].pri) {
        tree[x].ch[1] = merge(tree[x].ch[1], y);
        pushUp(x);
        return x;
    }
    else {
        tree[y].ch[0] = merge(x, tree[y].ch[0]);
        pushUp(y);
        return y;
    }
}
void split(int u, int k, int& x, int& y) {
    if (!u) {
        x = y = 0;
        return;
    }
    if (tree[u].val <= k) {
        x = u;
        split(tree[u].ch[1], k, tree[u].ch[1], y);
    }
    else {
        y = u;
        split(tree[u].ch[0], k, x, tree[u].ch[0]);
    }
    pushUp(u);
}
void insert(int val) {
    int x, y;
    split(root, val, x, y);
    root = merge(merge(x, newNode(val)), y);
}
void erase(int val) {
    int x, y, z;
    split(root, val, x, z);
    split(x, val - 1, x, y);
    if (y) {
        y = merge(tree[y].ch[0], tree[y].ch[1]);
    }
    root = merge(merge(x, y), z);
}
int getRankByVal(int val) {
    int x, y;
    split(root, val - 1, x, y);
    int rank = tree[x].size + 1;
    root = merge(x, y);
    return rank;
}
int getValByRank(int k) {
    int u = root;
    while (u) {
        int leftSize = tree[tree[u].ch[0]].size;
        if (leftSize + 1 == k) {
            return tree[u].val;
        }
        else if (leftSize >= k) {
            u = tree[u].ch[0];
        }
        else {
            k -= (leftSize + 1);
            u = tree[u].ch[1];
        }
    }
    return -1;
}
int getPrev(int val) {
    int x, y;
    split(root, val - 1, x, y);
    if (!x) return -1;
    int current_root = root;
    root = x;
    int res = getValByRank(tree[x].size);
    root = current_root;
    root = merge(x, y);
    return res;
}
int getNext(int val) {
    int x, y;
    split(root, val, x, y);
    if (!y) return -1;
    int current_root = root;
    root = y;
    int res = getValByRank(1);
    root = current_root;
    root = merge(x, y);
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    tree[0].size = 0;
    tree[0].pri = -1; // 优先级最低
    int n;
    cin >> n;
    for (int i = 1, x, opt; i <= n; ++i) {
        cin >> opt >> x;
        if (opt == 1) {
            insert(x);
        }
        else if (opt == 2) {
            erase(x);
        }
        else if (opt == 3) {
            cout << getRankByVal(x) << '\n';
        }
        else if (opt == 4) {
            cout << getValByRank(x) << '\n';
        }
        else if (opt == 5) {
            cout << getPrev(x) << '\n';
        }
        else {
            cout << getNext(x) << '\n';
        }
    }
    return 0;
}

const int MAXN = 100005;
Node tree[MAXN];
int tot, root;

void pushUp(int u) {
    if (u) {
        tree[u].size = tree[tree[u].ch[0]].size + tree[tree[u].ch[1]].size + 1;
    }
}
int newNode(int val) {
    tree[++tot] = Node(val);
    return tot;
}
int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (tree[x].pri > tree[y].pri) {
        tree[x].ch[1] = merge(tree[x].ch[1], y);
        pushUp(x);
        return x;
    }
    else {
        tree[y].ch[0] = merge(x, tree[y].ch[0]);
        pushUp(y);
        return y;
    }
}
void split(int u, int k, int& x, int& y) {
    if (!u) {
        x = y = 0;
        return;
    }
    if (tree[u].val <= k) {
        x = u;
        split(tree[u].ch[1], k, tree[u].ch[1], y);
    }
    else {
        y = u;
        split(tree[u].ch[0], k, x, tree[u].ch[0]);
    }
    pushUp(u);
}
void insert(int val) {
    int x, y;
    split(root, val, x, y);
    root = merge(merge(x, newNode(val)), y);
}
void erase(int val) {
    int x, y, z;
    split(root, val, x, z);
    split(x, val - 1, x, y);
    if (y) {
        y = merge(tree[y].ch[0], tree[y].ch[1]);
    }
    root = merge(merge(x, y), z);
}
int getRankByVal(int val) {
    int x, y;
    split(root, val - 1, x, y);
    int rank = tree[x].size + 1;
    root = merge(x, y);
    return rank;
}
int getValByRank(int k) {
    int u = root;
    while (u) {
        int leftSize = tree[tree[u].ch[0]].size;
        if (leftSize + 1 == k) {
            return tree[u].val;
        }
        else if (leftSize >= k) {
            u = tree[u].ch[0];
        }
        else {
            k -= (leftSize + 1);
            u = tree[u].ch[1];
        }
    }
    return -1;
}
int getPrev(int val) {
    int x, y;
    split(root, val - 1, x, y);
    if (!x) return -1;
    int current_root = root;
    root = x;
    int res = getValByRank(tree[x].size);
    root = current_root;
    root = merge(x, y);
    return res;
}
int getNext(int val) {
    int x, y;
    split(root, val, x, y);
    if (!y) return -1;
    int current_root = root;
    root = y;
    int res = getValByRank(1);
    root = current_root;
    root = merge(x, y);
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    tree[0].size = 0;
    tree[0].pri = -1; // 优先级最低
    int n;
    cin >> n;
    for (int i = 1, x, opt; i <= n; ++i) {
        cin >> opt >> x;
        if (opt == 1) {
            insert(x);
        }
        else if (opt == 2) {
            erase(x);
        }
        else if (opt == 3) {
            cout << getRankByVal(x) << '\n';
        }
        else if (opt == 4) {
            cout << getValByRank(x) << '\n';
        }
        else if (opt == 5) {
            cout << getPrev(x) << '\n';
        }
        else {
            cout << getNext(x) << '\n';
        }
    }
    return 0;
}