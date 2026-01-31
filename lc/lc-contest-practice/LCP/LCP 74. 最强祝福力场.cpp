#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// 寻找到最大的重叠区域
#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r

const int N = 1e3 + 7;
int sum[N<<2], lazy[N<<2];

void pushup(int rt) {
    sum[rt] = max(sum[ls], sum[rs]); 
}

void modify(int x, int val) {
    sum[x] += val;
    lazy[x] += val;
}

void pushdown(int rt) {
    if (lazy[rt]) {
        modify(ls, lazy[rt]);
        modify(rs, lazy[rt]);
        lazy[rt] = 0;
    }
}

void build(int rt, int l, int r) {
    sum[rt] = lazy[rt] = 0;
    if (l == r) {
        return;
    }
    build(lson);
    build(rson);
    pushup(rt);
}

void update(int rt, int l, int r, int L, int R, int val) {
    if (L <= l && r <= R) {
        modify(rt, val);
        return;
    }
    pushdown(rt);
    if (R <= mid) update(lson, L, R, val);
    else if (L > mid) update(rson, L, R, val);
    else {
        update(lson, L, mid, val);
        update(rson, mid+1, R, val);
    }
    pushup(rt);
}

class Solution {
public:
    int fieldOfGreatestBlessing(vector<vector<int>>& forceField) {
        int n = forceField.size();
        vector<vector<double>> line;
        vector<double> a;
        for (auto& rect : forceField) {
            double side = rect[2] * 1.0 / 2;
            a.push_back(rect[0] - side);
            a.push_back(rect[0] + side);
            line.push_back({rect[1] - side, rect[0] - side, rect[0] + side, 1});
            line.push_back({rect[1] + side + 0.01, rect[0] - side, rect[0] + side, -1});
        }
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        sort(line.begin(), line.end());
        int ans = 0, m = a.size();
        build(1, 0, m-1);
        int i = 0;
        while (i < line.size()) {
            int j = i;
            while (j < line.size() && line[j][0] == line[i][0]) {
                int l = lower_bound(a.begin(), a.end(), line[j][1]) - a.begin();
                int r = lower_bound(a.begin(), a.end(), line[j][2]) - a.begin();
                update(1, 0, m-1, l, r, line[j][3]);
                j++;
            }
            i = j;
            ans = max(ans, sum[1]);
        }
        return ans;
    }
};