// https://leetcode.cn/problems/online-majority-element-in-subarray/
// 投票算法本质上是在数组中不断找出两个不同的整数，把它们消除，所以说这个投票算法具有结合的性质
// 如果最后剩下的数字cnt>0那么表明有可能存在一个绝对众数，如果它真实的数量确实大于threshold，说明这个一定是绝对众数
// 这道题需要使用摩尔投票法+线段树，难度很高

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r
class MajorityChecker {
	int val[20010 * 4], cnt[20010 * 4], n;
	unordered_map<int, vector<int>> loc;
public:
	void pushup(int rt) {
		if (val[ls] == val[rs]) { val[rt] = val[ls], cnt[rt] = cnt[ls] + cnt[rs]; }
		else {
			if (cnt[ls] >= cnt[rs]) val[rt] = val[ls], cnt[rt] = cnt[ls] - cnt[rs];
			else val[rt] = val[rs], cnt[rt] = cnt[rs] - cnt[ls];
		}
	}
	void build(int rt, int l, int r, vector<int>& a) {
		if (l == r) { val[rt] = a[l - 1]; cnt[rt] = 1; return; }
		build(lson, a); build(rson, a); pushup(rt);
	}
	pair<int, int> query(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) return {val[rt], cnt[rt]};
		if (R <= mid) return query(lson, L, R);
		else if (L > mid) return query(rson, L, R);
		else {
			auto left = query(lson, L, mid);
			auto right = query(rson, mid + 1, R);
			if (left.first == right.first) return {left.first, left.second + right.second};
			else if (left.second >= right.second) return {left.first, left.second - right.second};
			else return {right.first, right.second - left.second};
		}
	}
    MajorityChecker(vector<int>& arr) {
    	n = arr.size();
    	memset(val, -1, sizeof(val));
    	memset(cnt, 0, sizeof(cnt));
    	build(1, 1, n, arr);
    	for (int i = 0; i < n; ++i) loc[arr[i]].push_back(i);
    }
    int query(int left, int right, int threshold) {
    	// 2 * threshold > right - left + 1，所以答案有且仅有一个，寻找的绝对众数
    	auto ans = query(1, 1, n, left + 1, right + 1);
		vector<int>& pos = loc[ans.first];
    	int tmp = upper_bound(pos.begin(), pos.end(), right) - lower_bound(pos.begin(), pos.end(), left);
    	return (tmp >= threshold ? ans.first : -1);
    }
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */