#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


#define ls rt * 2
#define rs rt * 2 + 1
#define mid ((l + r) / 2)
#define lson ls, l, mid
#define rson rs, mid + 1, r
// 这里的大小需要修改
#define Maxn 100010
typedef long long ll;
int a[Maxn<<2],n;
void pushup(int rt) {
    a[rt] = a[ls] + a[rs];
} // 向上合并的操作

void build(int rt, int l, int r, vector<int>&val) {
    if (l == r) {
        if (l == 0 || r == n-1 || val[l-1]>=val[l] || val[l+1]>=val[l]) a[rt]=0;
        else a[rt] = 1;
        return;
    }
    build(lson,val);
    build(rson,val);
    pushup(rt);
}
void update(int rt, int l, int r, int p, int v) {
    if (l == r) {
        a[rt] = v;
        return;
    }
    if (p <= mid) update(lson, p, v);
    else update(rson, p, v);
    pushup(rt);
}
// 这里的查询函数很灵活，有时需要返回一个结构体
ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return a[rt];
    }
    if (R <= mid) {
        return query(lson, L, R);
    } else if (L > mid) {
        return query(rson, L, R);
    }
    // 查询答案合并的操作，需要灵活变更
    else {
        return query(lson, L, mid) + query(rson, mid + 1, R);
    }
}
class Solution {
public:
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        n = nums.size();
        build(1,0,n-1,nums);
        vector<int> ans;
        for (auto& q : queries) {
            if (q[0] == 1) {
                int l = q[1], r = q[2];
                if (r-1 >= l+1)
                    ans.push_back(query(1,0,n-1,l+1,r-1));
                else ans.push_back(0);
            }
            else {
                int i = q[1];
                nums[i] = q[2];
                // 将可能产生三种变化
                if (i-1 >= 0) {
                    if (i-2 >= 0 && nums[i-1] > nums[i-2] && nums[i-1] > nums[i]) update(1,0,n-1,i-1,1);
                    else update(1,0,n-1,i-1,0);
                }
                if (i+1 < n) {
                    if (i+2 < n && nums[i+1] > nums[i+2] && nums[i+1] > nums[i]) update(1,0,n-1,i+1,1);
                    else update(1,0,n-1,i+1,0);
                }
                if (i-1 >= 0 && i+1 < n && nums[i] > nums[i-1] && nums[i] > nums[i+1]) {
                    update(1,0,n-1,i,1);
                }
                else update(1,0,n-1,i,0);
            }
        }
        return ans;
    }
};