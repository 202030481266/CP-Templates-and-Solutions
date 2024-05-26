#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

// 需要使用0的位置，不能使用位运算
#define lc rt*2
#define rc rt*2+1
#define mid ((l+r)/2)
#define lson lc,l,mid
#define rson rc,mid+1,r
// 这里的大小需要修改
#define Maxn 50010

int a[Maxn<<2];
const int inf = 0x3f3f3f3f;
struct node {
    int ms, ls, rs, s;
} tr[Maxn<<2];
void pushup(int rt) {
    tr[rt].s = max(-inf, tr[lc].s + tr[rc].s);
    tr[rt].ls = max(tr[lc].ls, max(-inf, tr[rc].ls + tr[lc].s));
    tr[rt].rs = max(tr[rc].rs, max(-inf, tr[lc].rs + tr[rc].s));
    tr[rt].ms = max(max(tr[lc].ms, tr[rc].ms), max(-inf, tr[lc].rs + tr[rc].ls));
}
void build(int rt, int l, int r) {
    if (l == r) {
        tr[rt].ls=tr[rt].rs=tr[rt].ms=tr[rt].s=1;
        return;
    }
    build(lson);
    build(rson);
    pushup(rt);
}
void update(int rt, int l, int r, int pos) {
    if (l == r) {
        tr[rt].ls=tr[rt].rs=tr[rt].ms=tr[rt].s=-inf;
        return;
    }
    if (pos <= mid) update(lson, pos);
    else update(rson, pos);
    pushup(rt);
}
node query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tr[rt];
    node x, y, w;
    if (R <= mid) w = query(lson, L, R);
    else if (L > mid) w = query(rson, L, R); 
    else {
        x = query(lson, L, mid);
        y = query(rson, mid+1, R);
        w.s = max(-inf,x.s + y.s);
        w.ms = max(max(x.ms, y.ms),max(-inf,x.rs+y.ls));
        w.ls = max(x.ls, max(-inf,x.s+y.ls));
        w.rs = max(y.rs, max(-inf,y.s+x.rs));
    }
    return w;
}

vector<bool> getResults(vector<vector<int>>& queries) {
    // 简单将就是判断[0,x]里面的最大字段和是否大于等于y
    vector<bool> ans;
    int n = min(50000, (int)queries.size()*3);
    build(1,1,n);
    for (auto q : queries) {
        if (q[0] == 1) {
            update(1, 1, n, q[1]); // [0,n]
        }
        else {
            if (q[1]-1 < 1) ans.push_back(q[2]<=1);
            else {
                node res1 = query(1, 1, n, 1, q[1]-1); // 不包含右端点, 此时区间必然有[0,q[1]]作为线段两端点
                node res2 = query(1, 1, n, q[1], q[1]); // 包含右端点
                // cout << res.ms << endl;
                ans.push_back(res1.ms >= q[2]-1 || res2.ms >= q[2]);
            }
        }
    }
    return ans;
}
class Solution {
    vector<int> t;

    // 把 i 处的值改成 val
    void update(int o, int l, int r, int i, int val) {
        if (l == r) {
            t[o] = val;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) {
            update(o * 2, l, m, i, val);
        } else {
            update(o * 2 + 1, m + 1, r, i, val);
        }
        t[o] = max(t[o * 2], t[o * 2 + 1]);
    }

    // 查询 [0,R] 中的最大值
    int query(int o, int l, int r, int R) {
        if (r <= R) {
            return t[o];
        }
        int m = (l + r) / 2;
        if (R <= m) {
            return query(o * 2, l, m, R);
        }
        return max(t[o * 2], query(o * 2 + 1, m + 1, r, R));
    }

public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int m = 0;
        for (auto& q : queries) {
            m = max(m, q[1]);
        }
        m++;

        set<int> st{0, m}; // 哨兵
        t.resize(2 << (32 - __builtin_clz(m)));

        vector<bool> ans;
        for (auto& q : queries) {
            int x = q[1];
            auto it = st.lower_bound(x);
            int pre = *prev(it); // x 左侧最近障碍物的位置
            if (q[0] == 1) {
                int nxt = *it; // x 右侧最近障碍物的位置
                st.insert(x);
                update(1, 0, m, x, x - pre);   // 更新 d[x] = x - pre
                update(1, 0, m, nxt, nxt - x); // 更新 d[nxt] = nxt - x
            } else {
                // 最大长度要么是 [0,pre] 中的最大 d，要么是 [pre,x] 这一段的长度
                int max_gap = max(query(1, 0, m, pre), x - pre);
                ans.push_back(max_gap >= q[2]);
            }
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> queries;
    // 打开输入文件
    std::ifstream inFile("testcase_cpp.txt");
    if (!inFile) {
        std::cerr << "无法打开输入文件" << std::endl;
        return 1;
    }

    // 打开输出文件
    std::ofstream outFile("testcase_cpp_result_right.txt");
    if (!outFile) {
        std::cerr << "无法打开输出文件" << std::endl;
        return 1;
    }

    // 读取输入文件中的每一行
    std::string line;
    while (getline(inFile, line)) {
        // 使用stringstream来解析每一行中的整数
        std::stringstream ss(line);
        int type, num1, num2;
        ss >> type;
        if (type == 1) {
            ss >> num1;
            queries.push_back({1,num1});
        } else if (type == 2) {
            ss >> num1 >> num2;
            queries.push_back({2,num1,num2});
        }
    }
    Solution sol;
    auto res = sol.getResults(queries);
    for (bool r : res) {
        outFile << r << endl;
    }
    // 关闭文件
    inFile.close();
    outFile.close();
}