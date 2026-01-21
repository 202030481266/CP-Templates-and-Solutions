#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;

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

void solve() {
    int n, m;
    cin >> n >> m;
    vi arr(n + 1);
    vi rank(n + 1), num(n + 1);
    vector<pii> b;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        b.emplace_back(arr[i], i);
    }
    ranges::sort(b);
    int N = 0;
    for (int i = 0; i < b.size(); ++i) {
        if (i == 0 || b[i].first != b[i - 1].first) {
            ++N;
            num[N] = b[i].first;
        }
        rank[b[i].second] = N;
    }
    FenwickSet f(N);
    vector<pii> qs(m);
    for (auto& [t, r] : qs) cin >> t >> r;
    vi pos{ m - 1 };
    int cur = qs[m - 1].first, p = qs[m - 1].second; 
    for (int i = m - 2; i >= 0; --i) {
        if (qs[i].second > p) {
            if (qs[i].first == cur) {
                pos.pop_back();
                pos.push_back(i);
                p = qs[i].second;
            }
            else {
                pos.push_back(i);
                cur = qs[i].first;
                p = qs[i].second;
            }
        }
    }
    for (int i = 1; i <= qs[pos.back()].second; ++i) f.add(rank[i], 1);
    vi c(n + 1);
    for (int i = (int)pos.size() - 1; i >= 0; --i) {
        int t = qs[pos[i]].first;
        int left = i == 0 ? 0 : qs[pos[i - 1]].second;
        if (t == 1) {
            for (int j = qs[pos[i]].second; j > left; --j) {
                c[j] = f.get_max();
                f.add(c[j], -1);
            }
        }
        else {
            for (int j = qs[pos[i]].second; j > left; --j) {
                c[j] = f.get_min();
                f.add(c[j], -1);
            }
        }
    }
    for (int i = qs[pos.back()].second + 1; i <= n; ++i) c[i] = rank[i];
    for (int i = 1; i <= n; ++i) {
        c[i] = num[c[i]];
        cout << c[i] << ' ';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
