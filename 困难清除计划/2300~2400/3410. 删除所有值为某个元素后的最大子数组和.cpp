#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 100010;

int n, m, a[maxn];
struct node { ll ms, ls, rs, s;} tr[maxn << 2];

#define lc rt << 1
#define rc rt << 1 | 1
#define mid ((l + r) >> 1)
#define lson lc, l, mid
#define rson rc, mid + 1, r

// 向上更新的操作就是区间合并的操作，我们在这里加入动态规划的核心操作
void pushup(int rt) {
    tr[rt].s = tr[lc].s + tr[rc].s;
    tr[rt].ls = max(tr[lc].ls, tr[rc].ls + tr[lc].s);
    tr[rt].rs = max(tr[rc].rs, tr[lc].rs + tr[rc].s);
    tr[rt].ms = max(max(tr[lc].ms, tr[rc].ms), tr[lc].rs + tr[rc].ls);
}

void build(int rt, int l, int r, vector<int>& nums) {
    if(l == r) {
        tr[rt].ls = tr[rt].rs = tr[rt].ms = tr[rt].s = nums[l-1];
        return;
    }
    build(lson, nums);
    build(rson, nums);
    pushup(rt);
}

void modify(int rt, int l, int r, int pos, int val) {
	// 单点修改，然后往上合并
    if(l == r) {
        tr[rt].s = tr[rt].ms = tr[rt].ls = tr[rt].rs = val;
        return;
    }
    if(pos <= mid) modify(lson, pos, val);
    else modify(rson, pos, val);
    pushup(rt);
}

// 这里的查询操作和动态规划是一个思路。
node query(int rt, int l, int r, int L, int R) {
    if(L <= l && r <= R) return tr[rt];
    node x, y, w;
    if(R <= mid) w = query(lson, L, R);
    else if(L > mid) w = query(rson, L, R);
    else {
        x = query(lson, L, mid);
        y = query(rson, mid + 1, R);
        w.s = x.s + y.s;
        w.ls = max(x.ls, x.s + y.ls);
        w.rs = max(y.rs, y.s + x.rs);
        w.ms = max(max(x.ms, y.ms), x.rs + y.ls);
    }
    return w;
}

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums) {
        int n = nums.size();
        bool flag = true;
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) {
                flag = false;
                break;
            }
        }
        if (flag) return *max_element(nums.begin(), nums.end());
        build(1, 1, n, nums);
        ll ans = tr[1].ms;
        unordered_map<int, int> mp;
        int type = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] < 0 && !mp.count(nums[i])) {
                mp[nums[i]] = type++;
            }
        }
        vector<vector<int>> group(type);
        for (int i = 0; i < n; ++i) {
            if (nums[i] < 0) {
                group[mp[nums[i]]].push_back(i + 1); 
            }
        }
        for (auto& g : group) {
            for (int& v : g) {
                modify(1, 1, n, v, 0);
            }
            ans = max(ans, tr[1].ms);
            for (int& v : g) {
                modify(1, 1, n, v, nums[v - 1]);
            }
        }
        return ans;
    }
};