// https://leetcode.cn/problems/longest-increasing-subsequence-ii/



int mx[400010];
class Solution {
public:
	void pushup(int rt) { mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]); }
	void update(int rt, int l, int r, int p, int val) {
		if (l == r) { mx[rt] = max(mx[rt], val); return ;}
		int mid = (l + r) >> 1;
		if (p <= mid) update(rt << 1, l, mid, p, val);
		else update(rt << 1 | 1, mid + 1, r, p, val);
		pushup(rt);
	}
	int query(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) return mx[rt];
		int mid = (l + r) >> 1;
		if (R <= mid) return query(rt << 1, l, mid, L, R);
		else if (L > mid) return query(rt << 1 | 1, mid + 1, r, L, R);
		else return max(query(rt << 1, l, mid, L, mid), query(rt << 1 | 1, mid + 1, r, mid + 1, R));
	}
    int lengthOfLIS(vector<int>& nums, int k) {
    	int n = nums.size(), f[n];
    	memset(f, 0, sizeof(f));
    	memset(mx, 0, sizeof(mx));
    	for (int i = 0; i < n; ++i) {
    		int L = max(1, nums[i] - k), R = nums[i] - 1;
    		if (L <= R) f[i] = query(1, 1, 100000, L, R);
    		++f[i];
    		update(1, 1, 100000, nums[i], f[i]);
    	}
    	return *max_element(f, f + n);
    }
};