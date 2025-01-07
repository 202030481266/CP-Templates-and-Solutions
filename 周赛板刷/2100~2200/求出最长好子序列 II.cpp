#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r
// 这里的大小需要修改
#define maxn 5000
int a[51][maxn*4];
void pushup(int rt, int id){ 
    a[id][rt] = max(a[id][ls], a[id][rs]);
} // 向上合并的操作
void update(int rt, int l, int r, int id, int p, int val) {
    if (l == r) {
        a[id][rt] = val;
        return;
    }
    if (p <= mid) update(lson, id, p, val);
    else update(rson, id, p, val);
    pushup(rt,id);
}
// 这里的查询函数很灵活，有时需要返回一个结构体
int query(int rt, int l, int r, int id, int L, int R) {
  if(L <= l && r <= R) { return a[id][rt]; }
  if(R <= mid) {return query(lson, id, L, R);}
  else if(L > mid) {return query(rson,id, L, R);}
  // 查询答案合并的操作，需要灵活变更
  else { return max(query(lson, id, L, mid) , query(rson, id, mid + 1, R));}
}
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        vector<int> arr(nums.begin(), nums.end());
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for (int& v : arr) {
            v = lower_bound(nums.begin(), nums.end(), v) - nums.begin()+1;
        }
        // dp[i][j] = max(dp[x][j])+1 or max(dp[y][j-1])+1
        memset(a, 0, sizeof(a));
        int ans = 0;
        for (int v : arr) {
            for (int j = 0; j <= k; ++j) {
                int dp_i_j = query(1, 1, n, j, v, v)+1;
                if (j > 0) {
                    if (v > 1) dp_i_j = max(dp_i_j, query(1, 1, n, j-1, 1, v-1)+1);
                    if (v < n) dp_i_j = max(dp_i_j, query(1, 1, n, j-1, v+1, n)+1);
                }
                ans = max(ans, dp_i_j);
                update(1, 1, n, j, v, dp_i_j);
            }
        }
        return ans;
    }
};