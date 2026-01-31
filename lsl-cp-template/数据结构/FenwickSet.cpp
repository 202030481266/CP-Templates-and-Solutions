class FenwickSet {
private:
	int n, tot;       // n: 值域上限, tot: 当前元素总数
	vector<int> tr;   // 树状数组
	int high_bit;     // 倍增搜索的起始位 (2^k)

public:
	// 初始化：size 为值域大小 (例如 1000000)
	FenwickSet(int size) : n(size), tot(0) {
		tr.assign(n + 1, 0);
		// 计算足够覆盖 n 的最大 2 的幂，例如 n=10^6 时 high_bit = 1<<19 或 1<<20
		high_bit = 1;
		while ((high_bit << 1) <= n) high_bit <<= 1;
	}

	// 基础修改：val 处增加 delta
	void add(int val, int delta) {
		tot += delta;
		for (; val <= n; val += val & -val) tr[val] += delta;
	}

	// 基础查询：前缀和 [1, val]
	int ask(int val) {
		int res = 0;
		for (; val > 0; val -= val & -val) res += tr[val];
		return res;
	}

	// --- 高级接口 ---

	// 插入元素
	void insert(int val) {
		add(val, 1);
	}

	// 删除元素 (安全删除：存在才删)
	void erase(int val) {
		// 通过前缀和差分判断是否存在：count = ask(val) - ask(val - 1)
		if (ask(val) > ask(val - 1)) {
			add(val, -1);
		}
	}

	// 查找第 k 小 (树上倍增，O(log n))
	int kth(int k) {
		if (k > tot) return -1;
		int pos = 0;
		for (int i = high_bit; i > 0; i >>= 1) {
			if (pos + i <= n && tr[pos + i] < k) {
				pos += i;
				k -= tr[pos];
			}
		}
		return pos + 1;
	}

	// 获取最大值
	int get_max() {
		return tot == 0 ? -1 : kth(tot);
	}

	// 获取最小值
	int get_min() {
		return tot == 0 ? -1 : kth(1);
	}

	// 当前集合大小
	int size() { return tot; }
};