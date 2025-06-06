// https://www.luogu.com.cn/problem/P4585
#include <bits/stdc++.h>

using namespace std;

struct Product {
    int s, v;
};

bool ProductCmp(Product a, Product b) {
    return a.s < b.s;
}

const int MAXN = 100001;
const int MAXT = 2000001;
const int BIT = 16;

int n, m, t;
int arr[MAXN];
int op[MAXN];
int s[MAXN];
int v[MAXN];
int sl[MAXN];
int sr[MAXN];
int x[MAXN];
int d[MAXN];
int tim[MAXN];

int root[MAXN];
int tree[MAXT][2];
int pass[MAXT];
int cntt;

int headp[MAXN << 2];
int nextp[MAXT];
int pid[MAXT];
int cntp;

int headb[MAXN << 2];
int nextb[MAXT];
int bid[MAXT];
int cntb;

Product product[MAXN];
int ans[MAXN];

int insert(int num, int i) {
    int rt = ++cntt;
    tree[rt][0] = tree[i][0];
    tree[rt][1] = tree[i][1];
    pass[rt] = pass[i] + 1;
    for (int b = BIT, path, pre = rt, cur; b >= 0; b--, pre = cur) {
        path = (num >> b) & 1;
        i = tree[i][path];
        cur = ++cntt;
        tree[cur][0] = tree[i][0];
        tree[cur][1] = tree[i][1];
        pass[cur] = pass[i] + 1;
        tree[pre][path] = cur;
    }
    return rt;
}

int query(int num, int u, int v) {
    int ansv = 0;
    for (int b = BIT, path, best; b >= 0; b--) {
        path = (num >> b) & 1;
        best = path ^ 1;
        if (pass[tree[v][best]] > pass[tree[u][best]]) {
            ansv += 1 << b;
            u = tree[u][best];
            v = tree[v][best];
        } else {
            u = tree[u][path];
            v = tree[v][path];
        }
    }
    return ansv;
}

void addInfoP(int i, int pi) {
    nextp[++cntp] = headp[i];
    pid[cntp] = pi;
    headp[i] = cntp;
}

void addInfoB(int i, int bi) {
    nextb[++cntb] = headb[i];
    bid[cntb] = bi;
    headb[i] = cntb;
}

void addProduct(int jobi, int pi, int l, int r, int i) {
    addInfoP(i, pi);
    if (l < r) {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            addProduct(jobi, pi, l, mid, i << 1);
        } else {
            addProduct(jobi, pi, mid + 1, r, i << 1 | 1);
        }
    }
}

void addBuy(int jobl, int jobr, int bi, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addInfoB(i, bi);
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            addBuy(jobl, jobr, bi, l, mid, i << 1);
        }
        if (jobr > mid) {
            addBuy(jobl, jobr, bi, mid + 1, r, i << 1 | 1);
        }
    }
}

int lower(int size, int num) {
    int l = 1, r = size, ansv = size + 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (product[mid].s >= num) {
            ansv = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ansv;
}

int upper(int size, int num) {
    int l = 1, r = size, ansv = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (product[mid].s <= num) {
            ansv = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ansv;
}

void dfs(int l, int r, int i) {
    int pcnt = 0;
    for (int e = headp[i]; e > 0; e = nextp[e]) {
        product[++pcnt].s = s[pid[e]];
        product[pcnt].v = v[pid[e]];
    }
    cntt = 0;
    for (int k = 1; k <= pcnt; k++) {
        root[k] = insert(product[k].v, root[k - 1]);
    }
    for (int e = headb[i], id, pre, post; e > 0; e = nextb[e]) {
        id = bid[e];
        pre = lower(pcnt, sl[id]) - 1;
        post = upper(pcnt, sr[id]);
        ans[id] = max(ans[id], query(x[id], root[pre], root[post]));
    }
    if (l < r) {
        int mid = (l + r) >> 1;
        dfs(l, mid, i << 1);
        dfs(mid + 1, r, i << 1 | 1);
    }
}

void prepare() {
    for (int i = 1; i <= n; i++) {
        root[i] = insert(arr[i], root[i - 1]);
    }
    vector<int> ids;
    for (int i = 1; i <= m; ++i) {
        if (op[i] == 0) {
            ids.push_back(i);
        }
        else {
            ans[i] = query(x[i], root[sl[i] - 1], root[sr[i]]);
            int start = max(tim[i] - d[i] + 1, 1);
            if (start <= tim[i]) {
                addBuy(start, tim[i], i, 1, t, 1);
            }
        }
    }
    sort(ids.begin(), ids.end(), [&](int i, int j) {
        return s[i] > s[j];
    });
    for (int& i : ids) {
        addProduct(tim[i], i, 1, t, 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    t = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> op[i];
        if (op[i] == 0) {
            t++;
            cin >> s[i] >> v[i];
        } else {
            cin >> sl[i] >> sr[i] >> x[i] >> d[i];
        }
        tim[i] = t;
    }
    prepare();
    dfs(1, t, 1);
    for (int i = 1; i <= m; i++) {
        if (op[i] == 1) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}