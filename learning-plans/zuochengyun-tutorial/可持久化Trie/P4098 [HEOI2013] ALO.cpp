// https://www.luogu.com.cn/problem/P4098
// 类似于dijkstra的技巧，每一次都是从全局最小值开始枚举，这样的话可以很容易获取左边和右边的最大值信息

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 5e4 + 7;
const int N = maxn * 35;
const int B = 30;

int n, tree[N][2], cnt[N], tot;
int last[maxn], next_pos[maxn], root[maxn];
vector<pii> arr;

int insert(int num, int x) {
    int rt = ++tot;
    tree[rt][0] = tree[x][0];
    tree[rt][1] = tree[x][1];
    cnt[rt] = cnt[x] + 1;
    
    for (int i = B, pre = rt, cur, b; i >= 0; --i) {
        b = (num >> i) & 1;
        x = tree[x][b];
        cur = ++tot;
        tree[cur][0] = tree[x][0];
        tree[cur][1] = tree[x][1];
        cnt[cur] = cnt[x] + 1;
        tree[pre][b] = cur;
        pre = cur;
    }
    return rt;
}

int query(int num, int l, int r) {
    int res = 0;
    for (int i = B, b; i >= 0; --i) {
        b = (num >> i) & 1;
        if (cnt[tree[r][b ^ 1]] - cnt[tree[l][b ^ 1]] > 0) {
            res |= 1 << i;
            l = tree[l][b ^ 1];
            r = tree[r][b ^ 1];
        } else {
            l = tree[l][b];
            r = tree[r][b];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first;
        arr[i].second = i + 1; // 1-n
        root[i + 1] = insert(arr[i].first, root[i]);
    }
    
    sort(arr.begin(), arr.end());
    
    // prepare the linked list
    last[0] = 0; next_pos[0] = 1;
    last[n + 1] = n; next_pos[n + 1] = n + 1;
    for (int i = 1; i <= n; ++i) {
        last[i] = i - 1;
        next_pos[i] = i + 1;
    }
    
    int ans = 0;
    for (int i = 0, l1, l2, r1, r2; i < n; ++i) {
        int id = arr[i].second; // 目前的全局最小值，所有值都比这个数值要大
        l1 = last[id];
        l2 = last[l1];
        r1 = next_pos[id];
        r2 = next_pos[r1];
        
        if (l1 != 0) {
            // (l2, r1)， 包含一个更大值l1
            ans = max(ans, query(arr[i].first, root[l2], root[r1 - 1]));
        }
        if (r2 != n + 1) {
            // (l1, r2)，包含一个更大值r1
            ans = max(ans, query(arr[i].first, root[l1], root[r2 - 1]));
        }
        
        next_pos[l1] = r1;
        last[r1] = l1;
    }
    
    cout << ans << '\n';
    return 0;
}