#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 实际上不需要扫描线，应该就是思维+排序
const int maxn = 2e5 + 7;
int mx[maxn<<2], a[maxn];

#define mid ((l+r)/2)
#define ls rt*2
#define rs rt*2+1
#define lson ls,l,mid
#define rson rs,mid+1, r

void update(int rt, int l, int r, int p, int val) {
    if (l==r) {
        a[l] = mx[rt] = val;
        return;
    }
    if (p <= mid) update(lson, p, val);
    else update(rson, p, val);
    mx[rt] = max(mx[ls], mx[rs]);
}
int query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return mx[rt];
    }
    if (R <= mid) return query(lson, L, R);
    else if (L > mid) return query(rson, L, R);
    else return max(query(lson, L, mid), query(rson, mid+1, R));
}

class Solution {
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int n = xCoord.size();
        vector<int> ids(n);
        vector<int> arr = xCoord;
        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        for (int& x : xCoord) {
            x = lower_bound(arr.begin(), arr.end(), x)-arr.begin();
        }
        iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int i, int j){
            return yCoord[i] == yCoord[j] ? xCoord[i] < xCoord[j] : yCoord[i] < yCoord[j];
        });
        int i = 0;
        vector<vector<int>> group;
        vector<int> ys;
        vector<int> tmp;
        while (i < n) {
            int j = i;
            tmp.clear();
            while (j < n && yCoord[ids[j]] == yCoord[ids[i]]) ++j;
            // [i, j)
            for (int k = i; k < j; ++k) {
                tmp.push_back(xCoord[ids[k]]);
            }
            if (!tmp.empty()) {
                ys.push_back(yCoord[ids[i]]);
                group.push_back(tmp);
            }
            i = j;
        }
        int m = group.size();
        int N = arr.size();
        ll ans = -1;
        memset(a, -1, sizeof(a));
        memset(mx, -1, sizeof(mx));
        for (int i = 0; i < m; ++i) {
            int len = group[i].size();
            for (int j = 0; j + 1 < len; ++j) {
                int left = group[i][j], right = group[i][j+1];
                if (a[left] > -1 && a[left] == a[right] && query(1, 0, N, left, right) == a[left]) {
                    int pre = a[left];
                    auto it = upper_bound(group[pre].begin(), group[pre].end(), left);
                    if (*it == right)
                        ans = max(ans, 1ll * (arr[right]-arr[left]) * (ys[i]-ys[pre]));
                }
            }
            for (int j = 0; j < len; ++j) {
                update(1, 0, N, group[i][j], i);
            }
        }
        return ans;
    }
};