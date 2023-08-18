// https://leetcode.cn/problems/handling-sum-queries-after-update/
// 线段树动态维护


#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r
#define Maxn 400010
int cnt0[Maxn], cnt1[Maxn], lazy[Maxn], arr[Maxn / 4];
class Solution {
	void pushup(int rt) {
		cnt0[rt] = cnt0[ls] + cnt0[rs];
		cnt1[rt] = cnt1[ls] + cnt1[rs];
	}
	void pushdown(int rt) {
		if (lazy[rt]) {
			lazy[rt] = 0;
			lazy[ls] ^= 1;
			lazy[rs] ^= 1;
			swap(cnt0[ls], cnt1[ls]);
			swap(cnt0[rs], cnt1[rs]);
		}
	}
	void build(int rt, int l, int r) {
		if (l == r) {
			if (arr[l]) ++cnt1[rt];
			else ++cnt0[rt];
			return;
		}
		build(lson);
		build(rson);
		pushup(rt);
	}
	void update(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			lazy[rt] ^= 1;
			swap(cnt0[rt], cnt1[rt]);
			return;
		}
		pushdown(rt);
		if (R <= mid) update(lson, L, R);
		else if (L > mid) update(rson, L, R);
		else {
			update(lson, L, mid);
			update(rson, mid + 1, R);
		}
		pushup(rt);
	}
	int query(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) return cnt1[rt];
		pushdown(rt);
		if (R <= mid) return query(lson, L, R);
		else if (L > mid) return query(rson, L, R);
		else return query(lson, L, mid) + query(rson, mid + 1, R);
	}
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
    	// 本质是维护区间中1的个数的问题
    	int n = nums1.size();
    	memset(cnt0, 0, sizeof(cnt0));
    	memset(cnt1, 0, sizeof(cnt1));
    	memset(lazy, 0, sizeof(lazy));
    	for (int i = 1; i <= n; ++i) arr[i] = nums1[i - 1];
    	build(1, 1, n);
    	long long cur = accumulate(nums2.begin(), nums2.end(), 0ll);
    	vector<long long> ans;
    	for (auto &q : queries) {
    		if (q[0] == 3) {
    			ans.emplace_back(cur);
    		}
    		else if (q[0] == 1) {
    			update(1, 1, n, q[1] + 1, q[2] + 1);
    		}
    		else {
    			cur += query(1, 1, n, 1, n) * 1ll * q[1];
    		}
    	}
    	return ans;
    }
};