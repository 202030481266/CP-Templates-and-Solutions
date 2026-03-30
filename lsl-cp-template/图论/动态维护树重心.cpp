#ifdef _MSC_VER
#include "pch.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector<vector<int>> vii;
typedef std::vector<ll> vl;
typedef std::vector<vector<ll>> vll;
typedef std::vector<pair<int, int>> vp;
typedef std::vector<vector<pair<int, int>>> vpp;

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char* x) { cerr << '\"' << x << '\"'; }
void __print(const string& x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template<typename T, typename V>
void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; }
template<typename T>
void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; }
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }

#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define debug(...)
#endif

static constexpr int MAXN = 500005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 1e9 + 7;
static constexpr int MAXB = 30;

// knowledge1: 一棵树最多有两个重心，并且是相邻的
// knowledge2: 必然是偶数的节点，删除两个重心之间的边之后，严格得到两个n/2的子树，这是充分必要条件
// knowledge3: 每个子树的大小都是小于等于floor(n/2)，那么只要从根出发，一直往最大的儿子走就行了，就可以找到重心
// guess1: 每一条边必然维护着两个连通块，ans = Min{ max(sz[a], sz[b]) - min(sz[a], sz[b]) } = Min { max(sz[x], n - sz[x]) - min(sz[x], n - sz[x]) }
// guess2: 每添加一个点本质上就是从自己开始走向祖先的所有的边增加1，然后我们只需要找到最为接近 (n + 1) / 2 的边，其实就是动态维护重心
// guess3: 重心最多移动一步（添加一个叶子节点），然后使用lca + 树上差分 + fenwick 维护子树的大小

// 动态树的重心 + 维护重心最大子树大小
// https://codeforces.com/problemset/problem/1827/D

const int LOG = 20;

// --- 树状数组 (Fenwick Tree) ---
struct FenwickTree {
	int n;
	vector<int> tree;

	void init(int _n) {
		n = _n;
		tree.assign(n + 1, 0);
	}

	void add(int i, int delta) {
		for (; i <= n; i += i & -i) tree[i] += delta;
	}

	int query(int i) {
		int sum = 0;
		for (; i > 0; i -= i & -i) sum += tree[i];
		return sum;
	}

	int query_range(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
};

// --- 树结构与重心维护 ---
struct DynamicCentroidTree {
	int n;
	vector<vector<int>> adj;

	// 基础信息
	int timer;
	vector<int> in, out, depth;
	vector<vector<int>> up;

	// HLD 专用维护数组
	vector<int> sz_final, heavy_child, head;
	// 优先队列维护轻儿子的动态 sz：pair<size, node_id>
	vector<priority_queue<pair<int, int>>> light_pq;

	FenwickTree bit;

	// 当前状态
	int current_centroid;
	int active_nodes_count;

	void init(int _n) {
		n = _n;
		adj.assign(n + 1, vector<int>());
		in.assign(n + 1, 0);
		out.assign(n + 1, 0);
		depth.assign(n + 1, 0);
		up.assign(n + 1, vector<int>(LOG, 0));

		// 初始化 HLD 结构
		sz_final.assign(n + 1, 0);
		heavy_child.assign(n + 1, 0);
		head.assign(n + 1, 0);
		light_pq.assign(n + 1, priority_queue<pair<int, int>>());

		bit.init(n);
		timer = 0;
		current_centroid = 0;
		active_nodes_count = 0;
	}

	void add_edge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// 第一遍 DFS：求倍增表、深度、最终静态子树大小、重儿子
	void dfs1(int u, int p) {
		up[u][0] = p;
		for (int i = 1; i < LOG; ++i) {
			up[u][i] = up[up[u][i - 1]][i - 1];
		}

		sz_final[u] = 1;
		int max_sub = 0;

		for (int v : adj[u]) {
			if (v != p) {
				depth[v] = depth[u] + 1;
				dfs1(v, u);
				sz_final[u] += sz_final[v];
				if (sz_final[v] > max_sub) {
					max_sub = sz_final[v];
					heavy_child[u] = v;
				}
			}
		}
	}

	// 第二遍 DFS：求 DFS 序、链头 (head)
	void dfs2(int u, int p, int h) {
		in[u] = ++timer;
		head[u] = h; // 记录当前节点所在重链的链头

		// 优先走重儿子（保证重链上的 DFS 序连续，虽本题不强求，但属于好习惯）
		if (heavy_child[u] != 0) {
			dfs2(heavy_child[u], u, h);
		}

		for (int v : adj[u]) {
			if (v != p && v != heavy_child[u]) {
				dfs2(v, u, v); // 轻儿子开启新的一条重链
			}
		}
		out[u] = timer;
	}

	void build(int root = 1) {
		depth[root] = 0;
		dfs1(root, 0);
		dfs2(root, 0, root);
	}

	bool is_ancestor(int u, int v) {
		if (u == 0) return true;
		return in[u] <= in[v] && out[u] >= out[v];
	}

	int get_child_towards(int u, int v) {
		for (int i = LOG - 1; i >= 0; --i) {
			if (depth[v] - (1 << i) > depth[u]) {
				v = up[v][i];
			}
		}
		return v;
	}

	// 动态添加叶子
	void activate_node(int v) {
		bit.add(in[v], 1);
		active_nodes_count++;

		// HLD 核心更新：顺着轻边往上跳，更新沿途父节点的轻儿子优先队列
		int curr = v;
		while (curr != 0) {
			int top_node = head[curr]; // 当前重链的链头
			int p = up[top_node][0];   // 链头的父节点
			if (p != 0) {
				// top_node 是 p 的轻儿子，将其当前真实大小压入 p 的优先队列
				int cur_sz = bit.query_range(in[top_node], out[top_node]);
				light_pq[p].push({ cur_sz, top_node });
			}
			curr = p; // 跳到父节点，继续往上
		}

		if (active_nodes_count == 1) {
			current_centroid = v;
			return;
		}

		while (true) {
			int C = current_centroid;
			int nxt = -1;
			int max_sub_size = 0;

			if (is_ancestor(C, v)) {
				nxt = get_child_towards(C, v);
				max_sub_size = bit.query_range(in[nxt], out[nxt]);
			}
			else {
				nxt = up[C][0];
				max_sub_size = active_nodes_count - bit.query_range(in[C], out[C]);
			}

			if (nxt != 0 && max_sub_size > active_nodes_count / 2) {
				current_centroid = nxt;
			}
			else {
				break;
			}
		}
	}

	// 获取最为接近 (n+1)/2 的子树大小
	int get_closest_size() {
		if (active_nodes_count == 0) return 0;

		int C = current_centroid;
		int sz_C = bit.query_range(in[C], out[C]);

		int max_child_sz = 0;

		// 1. 检查重儿子
		if (heavy_child[C] != 0) {
			max_child_sz = max(max_child_sz, bit.query_range(in[heavy_child[C]], out[heavy_child[C]]));
		}

		// 2. 检查轻儿子 (优先队列延迟删除)
		while (!light_pq[C].empty()) {
			auto [saved_sz, v] = light_pq[C].top();
			int actual_sz = bit.query_range(in[v], out[v]);
			if (saved_sz == actual_sz) {
				max_child_sz = max(max_child_sz, actual_sz);
				break;
			}
			else {
				light_pq[C].pop();
			}
		}

		// 关键修复：精确计算浮点数距离，并在距离相等时偏好较小的子树
		double target = (active_nodes_count + 1) / 2.0;
		double diff_C = abs(sz_C - target);
		double diff_child = abs(max_child_sz - target);

		// <= 保证了在距离相同时，优先选取较小的子节点
		if (max_child_sz > 0 && diff_child <= diff_C) {
			return max_child_sz;
		}

		return sz_C;
	}
};

void solve() {
	int n;
	cin >> n;
	DynamicCentroidTree tree;
	tree.init(n);
	for (int i = 2, fa; i <= n; ++i) {
		cin >> fa;
		tree.add_edge(fa, i);
	}
	tree.build(1);
	for (int i = 1; i <= n; ++i) {
		tree.activate_node(i);
		int ans = tree.get_closest_size();
		if (i >= 2) {
			cout << abs(i - 2 * ans) << ' ';
		}
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}