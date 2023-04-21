// https://leetcode.cn/problems/create-sorted-array-through-instructions/
// 平衡树模板题


struct Treap {
	// srand(123) 程序运行前记得设置随机数种子
	// 这里设置堆的性质为子权值大于等于父权值
	static const int maxn = 100005;
	int l[maxn], r[maxn], val[maxn], rnd[maxn], size_[maxn], w[maxn]; 
	// w数组记录的是值出现的次数
	// l和r数组记录的是左右儿子节点
	int sz, ans, rt;

	Treap() {
		sz = ans = rt = 0;
		memset(l, 0, sizeof(l));
		memset(r, 0, sizeof(r));
		memset(val, 0, sizeof(val));
		memset(rnd, 0, sizeof(rnd));
		memset(size_, 0, sizeof(size_));
		memset(w, 0, sizeof(w));
	}
	
	inline void pushup(int x) {
		size_[x] = size_[l[x]] + size_[r[x]] + w[x];
	}
	// 左旋操作
	void l_rotate(int& k) {
		int t = r[k];
		r[k] = l[t];
		l[t] = k;
		size_[t] = size_[k];
		pushup(k);
		k = t;
	}
	// 右旋操作
	void r_rotate(int& k) {
		int t = l[k];
		l[k] = r[t];
		r[t] = k;
		size_[t] = size_[k];
		pushup(k);
		k = t;
	}
	void insert(int& k, int x) {
		if (!k) {
			k = ++sz;
			size_[k] = 1;
			w[k] = 1;
			val[k] = x;
			rnd[k] = rand();  // 设置随机数权值
			return;
		}
		++size_[k];
		if (val[k] == x) {
			++w[k];
		}
		else if (val[k] < x) {
			insert(r[k], x);
			if (rnd[r[k]] < rnd[k]) l_rotate(k);
		}
		else {
			insert(l[k], x);
			if (rnd[l[k]] < rnd[k]) r_rotate(k);
		}
	}
	bool del(int& k, int x) {
		if (!k) return false;
		if (val[k] == x) {
			if (w[k] > 1) {
				--w[k];
				--size_[k];
				return true;
			}
			if (l[k] == 0 || r[k] == 0) {
				k = l[k] + r[k];
				return true;
			}
			else if (rnd[l[k]] < rnd[r[k]]) {
				r_rotate(k);
				return del(k, x);
			} 
			else {
				l_rotate(k);
				return del(k, x);
			}
		}
		else if (val[k] < x) {
			bool ok = del(r[k], x);
			if (ok) --size_[k];
			return ok;
		}
		else {
			bool ok = del(l[k], x);
			if (ok) --size_[k];
			return ok;
		}
	}
	// 查询x的排名有多大（第k小）
	int queryRank(int k, int x) {
		if (!k) return 0;
		if (val[k] == x) return size_[l[k]] + 1;
		else if (val[k] < x) return queryRank(r[k], x) + w[k] + size_[l[k]];
		else return queryRank(l[k], x);
	}
	// 查询排名为x的数字
	int queryNum(int k, int x) {
		if (!k) return 0;
		if (x <= size_[l[k]]) return queryNum(l[k], x);
		else if (x > size_[l[k]] + w[k]) return queryNum(r[k], x - size_[l[k]] - w[k]);
		else return val[k];
	}
	// 查找x的前驱 （第一个比x小的数）
	void queryPre(int k, int x) {
		if (!k) return;
		if (val[k] < x) {
			ans = k;
			queryPre(r[k], x);
		}
		else {
			queryPre(l[k], x);
		}
	}
	// 查找x的后继（第一个比x大的数）
	void querySub(int k, int x) {
		if (!k) return;
		if (val[k] > x) {
			ans = k;
			querySub(l[k], x);
		}
		else {
			querySub(r[k], x);
		}
	}
};
class Solution {
	static constexpr int mod = 1000000007;
public:
    int createSortedArray(vector<int>& instructions) {
    	int n = instructions.size(), ans = 0, total = 0;
		srand(123);
    	unordered_map<int, int> cnt;
		Treap tree;
    	for (int x : instructions) {
    		tree.insert(tree.rt, x);
    		++cnt[x], ++total;
    		int rank = tree.queryRank(tree.rt, x);
    		ans = (ans + min(rank - 1, total - rank - cnt[x] + 1)) % mod;
    	}
    	return ans;
    }
};