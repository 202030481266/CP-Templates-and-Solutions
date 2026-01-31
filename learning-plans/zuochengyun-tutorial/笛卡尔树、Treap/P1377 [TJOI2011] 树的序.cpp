// 利用笛卡尔树的 O(n) 建树的方法来构建二叉搜索树，一般来说我们都是要让key作为二叉搜索树
/*
    key: 1, 3, ,4, 2
    value: 1, 2, 3, 4
*/ 

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int arr[MAXN], ls[MAXN], rs[MAXN],n;
int tot = 0;

void dfs(int u, vector<int>& a) {
    ++tot;
    if (tot < n) printf("%d ", a[u]);
    else printf("%d\n", a[u]);
    if (ls[u] != -1) dfs(ls[u], a);
    if (rs[u] != -1) dfs(rs[u], a);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<int> a(n), b(n);
    for (auto& v : a) cin >> v;
    iota(b.begin(), b.end(), 0);
    vector<int> ids(n);
    iota(ids.begin(), ids.end(), 0);

    sort(ids.begin(), ids.end(), [&](int i, int j){
        return a[i] < a[j];
    });

    memset(ls, -1, sizeof(ls));
    memset(rs, -1, sizeof(rs));
    
    int top = 0; // [0, top)
    for (int i : ids) {
        int p = top;
        while (p > 0 && b[arr[p-1]] > b[i]) --p;
        if (p > 0) rs[arr[p-1]] = i;
        if (p < top) ls[i] = arr[p];
        arr[p++] = i;
        top = p;
    }
    
    dfs(0, a);
    
}