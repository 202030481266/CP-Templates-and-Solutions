// https://leetcode.cn/problems/rectangle-area-ii/

#define lson (rt<<1)
#define rson (rt<<1|1)
typedef long long ll;
struct ScanLine {
	ll l, r, h, mark;
	ScanLine(): l(0), r(0), h(0), mark(0) {}
	ScanLine(ll _l, ll _r, ll _h, ll _mark): l(_l), r(_r), h(_h), mark(_mark) {}
	bool operator < (const ScanLine &rhs) const { return h < rhs.h; }
};
struct SegTree {
	int l, r, sum; ll len;
	SegTree(): l(0), r(0), sum(0), len(0) {}
};
class Solution {
	static constexpr int N = 10010, mod = 1000000007;
	int X[N];
	ScanLine line[N];
	SegTree tree[N];
	void build(int rt, int l, int r) {
		tree[rt].l = l, tree[rt].r = r;
		tree[rt].len = tree[rt].sum = 0;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(lson, l, mid);
		build(rson, mid + 1, r);
		return;
	}
	void pushup(int rt) {
		int l = tree[rt].l, r = tree[rt].r;
		if (tree[rt].sum) tree[rt].len = X[r + 1] - X[l]; // 这个线段区间被覆盖过
		else tree[rt].len = tree[lson].len + tree[rson].len;
	}
	void update(int rt, ll L, ll R, int c) {
		int l = tree[rt].l, r = tree[rt].r;
		if (X[r + 1] <= L || R <= X[l]) return;
		if (L <= X[l] && X[r + 1] <= R) {
			tree[rt].sum += c; // 增加c次覆盖
			pushup(rt);
			return;
		}
		update(lson, L, R, c);
		update(rson, L, R, c);
		pushup(rt);
	}
public:
    int rectangleArea(vector<vector<int>>& rect) {
    	int n = rect.size();
    	for (int i = 1; i <= n; ++i) {
    		X[2 * i - 1] = rect[i - 1][0], X[2 * i] = rect[i - 1][2];
    		line[2 * i - 1] = ScanLine(rect[i - 1][0], rect[i - 1][2], rect[i - 1][1], 1);
    		line[2 * i] = ScanLine(rect[i - 1][0], rect[i - 1][2], rect[i - 1][3], -1);
    	}
    	n <<= 1;
    	// 离散化
    	sort(line + 1, line + n + 1);
    	sort(X + 1, X + n + 1);
    	int tot = unique(X + 1, X + n + 1) - X - 1;
    	build(1, 1, tot - 1);
    	ll ans = 0;
    	for (int i = 1; i < n; ++i) {
    		// 最后一条边是不需要管的
    		update(1, line[i].l, line[i].r, line[i].mark);
    		ans = (ans + tree[1].len * (line[i + 1].h - line[i].h)) % mod;
    	}
    	return ans;
    }
};