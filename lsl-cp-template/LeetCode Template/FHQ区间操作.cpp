// 题目：
// 三种操作
// 1 set index value
// 2 query the xor sum of [left, right]
// 3 reverse subarray of [left, right]

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// 区间反转是难点
// FHQ
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int val, pri, size, ch[2], rev, xsum;
    Node(int v = 0) : val(v), xsum(0), pri(rng()), size(1), ch{ 0, 0 }, rev(0) {}
};

const int maxn = 100007;
Node tree[maxn];
int tot, root;

void pushup(int u) {
    if (u) {
        tree[u].size = tree[tree[u].ch[0]].size + tree[tree[u].ch[1]].size + 1;
        tree[u].xsum = tree[tree[u].ch[0]].xsum ^ tree[tree[u].ch[1]].xsum ^ tree[u].val;
    }
}
void pushdown(int u) { // lazy update, (ab)^r = (b^r)(a^r)
    if (tree[u].rev) {
        swap(tree[u].ch[0], tree[u].ch[1]);
        tree[tree[u].ch[0]].rev ^= 1;
        tree[tree[u].ch[1]].rev ^= 1;
        tree[u].rev = 0;
    }
}
int newNode(int val) {
    tree[++tot] = Node(val);
    return tot;
}
int merge(int x, int y) {
    if (!x || !y) {
        pushup(x + y); // don't forget update the xsum
        return x + y;
    }
    if (tree[x].pri > tree[y].pri) {
        pushdown(x);
        tree[x].ch[1] = merge(tree[x].ch[1], y);
        pushup(x);
        return x;
    }
    else {
        pushdown(y);
        tree[y].ch[0] = merge(x, tree[y].ch[0]);
        pushup(y);
        return y;
    }
}
void split(int u, int rank, int& x, int& y) {
    if (!u) {
        x = y = 0;
        return;
    }
    pushdown(u);
    if (tree[tree[u].ch[0]].size + 1 <= rank) {
        x = u;
        split(tree[u].ch[1], rank - tree[tree[u].ch[0]].size - 1, tree[x].ch[1], y);
    }
    else {
        y = u;
        split(tree[u].ch[0], rank, x, tree[y].ch[0]);
    }
    pushup(u);
}

class Solution {
public:
    vector<int> getResults(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        tot = 0;
        root = 0;
        tree[0].size = 0;
        tree[0].pri = -1;
        for (int& v : nums) {
            root = merge(root, newNode(v));
        }
        vector<int> ans;
        for (auto& q : queries) {
            int opt = q[0];
            if (opt == 1) {
                int index = q[1] + 1, value = q[2];
                int x, y, z;
                split(root, index, x, y); // x <= index, y > index
                split(x, index-1, x, z); // x <= index-1, z == index
                tree[z].val = value;
                root = merge(merge(x, z), y);
            }
            else {
                int left = q[1] + 1, right = q[2] + 1;
                int x, y, z;
                split(root, left-1, x, y); // x <= left-1, y >= left
                split(y, right-left+1, y, z); // left <= y <= right, z > right
                if (opt == 2) {
                    ans.push_back(tree[y].xsum);
                }
                else {
                    tree[y].rev ^= 1;
                }
                root = merge(x, merge(y, z));
            }
        }
        return ans;
    }
};