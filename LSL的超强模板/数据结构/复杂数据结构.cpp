// LeetCode常用的数据结构
// 稀疏表
template<typename T>
struct ST {
	// index start from 0
	int N;
	vector<vector<T>> vec;

	ST() { N = 0; }
	ST(int n) {
		N = n;
		vec.resize(N);
		for (auto& v : vec) v = vector<T>(30, 0);
		for (int i = 0; i < N; i++) {
			cin >> vec[i][0];
		}
	}
	ST(const vector<T>& a) {
		vec.resize(a.size());
		N = a.size();
		for (auto& v : vec) v = vector<T>(30, 0);
		for (int i = 0; i < N; i++) vec[i][0] = a[i];
	}
	void ST_work() {
		int t = log(N) / log(2) + 1;
		for (int i = 1; i < t; i++) {
			for (int j = 0; j + (1 << i) - 1 < N; j++) {
				vec[j][i] = max(vec[j][i - 1], vec[j + (1 << (i - 1))][i - 1]);
			}
		}
	}
	void ST_debug() {
		// 打印调试ST表
		int t = log(N) / log(2) + 1;
		for (int i = 0; i < t; i++) {
			cout << "the length of step is " << (1 << i) << endl;
			for (int j = 0; j + (1 << i) - 1 < N; j++) {
				cout << "now on start from index " << j << ' ';
				cout << "value is " << vec[j][i] << endl;
			}
		}
	}
	T query(int l, int r) {
		int k = log(r - l + 1) / log(2);
		return max(vec[l][k], vec[r - (1 << k) + 1][k]);
	}
	int lower_bound(int l, int r, T val) {
		// first position k that max{l,.....,k} >= val
		int start = l, res = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			T temp = query(start, mid);
			if (temp >= val) res = mid, r = mid - 1;
			else l = mid + 1;
		}
		return res;
	}
};
// 一维树状数组
// 维护的是长为lowbit(i)长度的数组和
// 区间修改，单点查询 -> 维护差分序列
// 区间修改，区间查询 -> 维护两个树状数组即可，一个维护(sum(pi))，一个维护(sum(i * pi))
// sum[r] = (r+1)*query1(r)-query2(r)
template<typename T>
struct Fenwick {
	// index from 0 to N - 1
	int N;
	vector<T> vec;

	Fenwick() { N = 0; }
	Fenwick(int n) {
		vec.resize(n);
		N = n;
	}
	void update(int pos, T val) {
		// update a[pos]
		for (; pos < N; pos |= pos + 1) vec[pos] += val;
	}
	T query(int pos) {
		// sum of [0, pos)
		T res = 0;
		for (; pos > 0; pos &= pos - 1) res += vec[pos - 1];
		return res;
	}
	// just for positive value
	int lower_bound(T val) {
		// first position that sum[0...p] >= val
		// empty sum return -1, no position return N
		if (val <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= N && vec[pos + pw - 1] < val)
				pos += pw, val -= vec[pos - 1];
		}
		return pos;
	}
};
// 二维树状数组
// 维护的是一个长为lowbit(i),宽为lowbit(j)的矩阵和
// 介绍的比较好的博客链接：https://www.cnblogs.com/hbhszxyb/p/14157271.html
// 区间修改和单点查询,作二维差分数组，d[i][j]=a[i][j]-a[i-1][j]-a[i][j-1]+a[i-1][j-1]
/*
# 更新时分别对矩阵四个角做如下更新(左上角为原点)
# 左上角坐标(x1,y1),右下角坐标(x2,y2)
# 更新时在(x1,y1)处 +x,相当于对矩阵 (x1,y1)到(n,m)都加上了x
# 在(x1,y2+1)处-x,消除对矩阵(x1,y2+1)到(n,m)多加的x
# 在(x2+1,y1)处-x,消除对矩阵(x2+1,y1)到(n,m)多加的x
# 在(x2+1,y2+1)处+x,(x2+1,y2+1)到(n,m)被上面三个操作都就算了一遍，被加了一次x，减去两次x,
# 所以再加一次x消除影响。
0  0  0  0  0
0 +x  0  0 -x
0  0  0  0  0
0  0  0  0  0
0 -x  0  0 +x
# 单点getsum求值时，矩阵结果如下：
0  0  0  0  0
0  x  x  x  0
0  x  x  x  0
0  x  x  x  0
0  0  0  0  0
*/
// 区间修改和区间取和，d[i][j]在前缀和sum[x][y]里面出现了(x-i+1)(y-j+1)次
// 维护四个数组：d[i][j], d[i][j]*i, d[i][j]*j, d[i][j]*i*j
// sum[x][y] = (x+1)(y+1)query1(x,y)-(y+1)query2(x,y)-(x+1)query3(x,y)+query4(x,y)
template<typename T>
struct Fenwick_2d {
	// row from 1 to N
	// column from 1 to M
	vector<vector<T>> vec;
	int N, M;

	Fenwick_2d() { N = M = 0; }
	Fenwick_2d(int n, int m) {
		N = n + 1;
		M = m + 1;
		vec.resize(N);
		for (auto& v : vec) v = vector<T>(M, 0);
	}
	int lowbit(int x) { return x & (-x); }
	void update(int x, int y, T val) {
		// a[x][y] += val
		for (int i = x; i < N; i += lowbit(i))
			for (int j = y; j < M; j += lowbit(j))
				vec[i][j] += val;
	}
	T query(int x, int y) {
		// get [1,1] ~ [x, y] matrix sum
		T res = 0;
		for (int i = x; i > 0; i -= lowbit(i))
			for (int j = y; j > 0; j -= lowbit(j))
				res += vec[i][j];
		return res;
	}
};
// 并查集，按秩合并
class UnionFind {
public:
	// index from 0 to n - 1
	vector<int> parent, size;
	int n, setCount;
public:
	UnionFind(int _n) : n(_n), setCount(_n), parent(_n), size(_n, 1) {
		iota(parent.begin(), parent.end(), 0);
	}
	int find(int x) {
		return parent[x] == x ? x : parent[x] = find(parent[x]);
	}
	bool unite(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) return false;
		if (size[x] < size[y]) swap(x, y);
		parent[y] = x;
		size[x] += size[y];
		--setCount;
		return true;
	}
	bool connected(int x, int y) {
		return find(x) == find(y);
	}
};
// 单调队列
struct Queue {
	// index from 1 to n
	// K is size of sliding window
	int N, st, ed, K;
	vector<int> Q, a;

	Queue() { N = st = ed = K = 0; }
	Queue(int n, int k) {
		st = ed = 0;
		K = k;
		N = n;
		Q.resize(N + 1);
		a.resize(N + 1);
		// 输入数组里面的数字
		for (int i = 1; i <= N; i++) cin >> a[i];
	}
	Queue(const vector<int>& rhs, int k) {
		st = ed = 0;
		K = k;
		N = rhs.size();
		Q.resize(N + 1);
		a.resize(N + 1);
		for (int i = 1; i <= N; i++) a[i] = rhs[i - 1];
	}
	// 获取到滑动窗口到达的每一个位置的最小值
	vector<int> get_min() {
		st = ed = 0;
		vector<int> Minn(N + 1, INT_MAX);
		Q[ed++] = 1;
		Minn[1] = a[1];
		for (int i = 2; i <= N; i++) {
			while (st < ed && a[i] < a[Q[ed - 1]]) --ed;
			Q[ed++] = i;
			while (st < ed && Q[st] < i - K + 1) ++st;
			Minn[i] = a[Q[st]];
		}
		return Minn;
	}
	// 获取到滑动窗口到达的每一个位置的最大值
	vector<int> get_max() {
		st = ed = 0;
		vector<int> Maxx(N + 1, INT_MIN);
		Q[ed++] = 1;
		Maxx[1] = a[1];
		for (int i = 2; i <= N; i++) {
			while (st < ed && a[i] > a[Q[ed - 1]]) --ed;
			Q[ed++] = i;
			while (st < ed && Q[st] < i - K + 1) ++st;
			Maxx[i] = a[Q[st]];
		}
		return Maxx;
	}
};

// 力扣数据流难题汇总，基本都是数据结构的问题所以汇总写在这里（此类问题一般使用有序数据结构解决）
// 数据流的中位数，本质问题就是维护动态序列的中位数，根据中位数的性质，那么可以使用两个堆来维护。
// 大根堆存储一半的小于中位数的数，小根堆存储大于中位数的一半的数。
class MedianFinder {
public:
	priority_queue<int, vector<int>, less<int>> queMin; // 大根堆
	priority_queue<int, vector<int>, greater<int>> queMax; // 小根堆
	
	MedianFinder() {}

	void addNum(int num) {
		if (queMin.empty() || num <= queMin.top()) {
			queMin.push(num);
			// 调整大小，保证大根堆的大小最多比小根堆大1
			if (queMax.size() + 1 < queMin.size()) {
				queMax.push(queMin.top());
				queMin.pop();
			}
		}
		else {
			queMax.push(num);
			// 调整大小，保证小根堆的大小不能大于大根堆
			if (queMax.size() > queMin.size()) {
				queMin.push(queMax.top());
				queMax.pop();
			}
		}
	}
	double findMedian() {
		// 根据堆的大小来返回中位数，大根堆包含的数大于等于小根堆的数
		if (queMin.size() > queMax.size()) 
			return queMin.top();
		return (queMin.top() + queMax.top()) / 2.0;
	}
};
// 求解MK平均值https://leetcode.cn/problems/finding-mk-average/
// 本质维护一个大小为M的队列的其中位于[k+1,M-k+1]的区间平均数
/*
	这道题的做法相当巧妙，很明显这里的序列被分为了三个段，所以单纯使用大小根堆的方法是维护不了的。解法
为使用三个有序集合s1,s2,s3分别维护这三段序列的数。那么就可以讨论了。当队列的大小小于等于M的时候，就
可以直接放进队列，同时把数字num放进s2中。大小等于M的时候，就把最小的k个数放进s1，最大的k个放进s2。
	那么如果队列的大小大于M了，此时就要弹出后面的数字，其实，这个时候先去讨论新数字的关系（原来关系）
num<s1的最大元素,那么明显可以知道,它一定在s1中，同时要把s1中的最大数字放到s2中；反之如果num>s3中的最
小元素，那么num一定s3中，此时则把s3的最小元素放到s2中。如果都不是，那么它就在s2中。
	这时候再去看删除数字num=q.front()的问题，无论上面如何操作，都会发现s2肯定多了一个元素，s1或者s2
少了一个元素，如果num在s1中，就可以删除num，并且s2取走最小的一个数放s2中。相同操作对于s3。可以证明
这个数不会同时出现在s1或者s3中。
*/
class MKAverage {
private:
	int m, k;
	queue<int> q;
	multiset<int> s1, s2, s3;
	long long sum2;  // 维护的是s2集合里面的数字的和
public:
	MKAverage(int m, int k) : m(m), k(k) {
		sum2 = 0;
	}
	void addElement(int num) {
		q.push(num);
		if (q.size() <= m) {
			s2.insert(num);
			sum2 += num;
			// 如果队列的大小等于m就需要进行s1,s3的赋值
			if (q.size() == m) {
				while (s1.size() < k) {
					s1.insert(*s2.begin());
					sum2 -= *s2.begin();
					s2.erase(s2.begin());
				}
				while (s3.size() < k) {
					s3.insert(*s2.rbegin());
					sum2 -= *s2.rbegin();
					s2.erase(prev(s2.end()));
				}
			}
			return;
		}
		if (num < *s1.rbegin()) {
			s1.insert(num);
			s2.insert(*s1.rbegin());
			sum2 += *s1.rbegin();
			s1.erase(prev(s1.end()));
		}
		else if (num > *s3.begin()) {
			s3.insert(num);
			s2.insert(*s3.begin());
			sum2 += *s3.begin();
			s3.erase(s3.begin());
		}
		else {
			s2.insert(num);
			sum2 += num;
		}
		int x = q.front();
		q.pop();
		if (s1.count(x) > 0) {
			s1.erase(s1.find(x));
			s1.insert(*s2.begin());
			sum2 -= *s2.begin();
			s2.erase(s2.begin());
		}
		else if (s3.count(x) > 0) {
			s3.erase(s3.find(x));
			s3.insert(*s2.rbegin());
			sum2 -= *s2.rbegin();
			s2.erase(prev(s2.end()));
		}
		else {
			s2.erase(s2.find(x));
			sum2 -= x;
		}
	}
	int calculateMKAverage() {
		if (q.size() < m) 
			return -1;
		return sum2 / (m - 2 * k);
	}
};
// 下面这道题的解法和维护中位数很像，一个维护单调递增的前K个最大的数，一个维护其他的数。
struct landscape {
	string name;
	int val;
	landscape() {
		val = 0;
		name = "";
	}
	landscape(string _n, int _v) : name(_n), val(_v) {}
	// 注意了，如果要同时使用大小根堆则需要定义两个比较符号。
	bool operator < (const landscape& rhs) const {
		if (rhs.val != this->val) return this->val < rhs.val;
		else return this->name > rhs.name;
	}
	bool operator > (const landscape& rhs) const {
		if (rhs.val != this->val) return this->val > rhs.val;
		else return this->name < rhs.name;
	}
};
class SORTracker {
public:
	priority_queue<landscape, vector<landscape>, less<landscape>> q_max;
	priority_queue<landscape, vector<landscape>, greater<landscape>> q_min;
	SORTracker() {}
	void add(string name, int score) {
		q_max.push(landscape(name, score));
	}
	string get() {
		q_min.push(q_max.top());
		q_max.pop();
		while (q_min.top() < q_max.top()) {
			q_max.push(q_min.top());
			q_min.push(q_max.top());
			q_min.pop();
			q_max.pop();
		}
		return q_min.top().name;
	}
};

// 字典树（不同写法的速度有非常大的差别）
// 下面为力扣的写法,插入速度为870ms（10000个100长度字符串），速度真的是慢飞天！！主要耗时空间开辟。
class Trie {
private:
	vector<Trie*> children;
	bool isEnd;

	Trie* searchPrefix(string prefix) {
		Trie* node = this;
		for (char ch : prefix) {
			ch -= 'a';
			if (node->children[ch] == nullptr) {
				return nullptr;
			}
			node = node->children[ch];
		}
		return node;
	}

public:
	Trie() : children(26), isEnd(false) {}

	void insert(string word) {
		Trie* node = this;
		for (char ch : word) {
			ch -= 'a';
			if (node->children[ch] == nullptr) {
				node->children[ch] = new Trie();
			}
			node = node->children[ch];
		}
		node->isEnd = true;
	}

	bool search(string word) {
		Trie* node = this->searchPrefix(word);
		return node != nullptr && node->isEnd;
	}

	bool startsWith(string prefix) {
		return this->searchPrefix(prefix) != nullptr;
	}
};
// 下面为使用数组的写法，速度大约为47ms（10000个100长度字符串）
struct MyTrie {
	static const int Maxn = 1000001;
	int ch[Maxn][26], val[Maxn], sz;
	void init() {
		sz = 0; 
		memset(val, 0, sizeof(val));
		memset(ch[0], 0, sizeof(ch[0]));
	}
	void insert(string s) {
		int u = 0, len = s.size();
		for (int i = 0; i < len; i++) {
			int v = s[i] - 'a';
			if (!ch[u][v]) { ch[u][v] = ++sz; memset(ch[sz], 0, sizeof(ch[sz])); }
			u = ch[u][v]; val[u]++;
		}
	}
	void query(string s) {
		int u = 0, len = s.size();
		for (int i = 0; i < len; i++) {
			int v = s[i] - 'a';
			u = ch[u][v];
			// cout<<s[i]<<val[u]<<endl;
			if (val[u] == 0) break;
		}
	}
};

// 平衡树数据结构太多了，但是性能参差不齐。本STL只实现treap,splay（因为本来就是刷题用的）
// 下面的是旋转treap平衡树的实现，因为treap很难被卡，在做题的时候常数一般来说很小。
// STL一般来说很难被卡，开了O2优化之后基本无敌，能够吊打绝大多数数据结构，所以看情况使用
struct Treap {
	// srand(123) 程序运行前记得设置随机数种子
	// 这里设置堆的性质为子权值大于等于父权值
	static const int maxn = 100005;
	int l[maxn], r[maxn], val[maxn], rnd[maxn], size_[maxn], w[maxn]; 
	// w数组记录的是值出现的次数
	// l和r数组记录的是左右儿子节点
	int sz, ans, rt;
	
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
// 在浏览洛谷平衡树题解社区中水到了一种看起来很牛逼的数据结构：01trie，据说常数能够吊打线段树？
// 虽然加强版的平衡树题目有各种方法可以去过掉，但是我觉得还是老老实实写平衡树就OK了。
// 下面是01trie的实现，实际上是一种完全二叉树，非常吃空间，但是速度还是非常快的！！
// 100000次插入，Treap和STL差不多都是30ms，01Trie只需要5ms。
struct Trie_01 {
	// 只能使用在正整数上，所以对于负数可以加上一个很大的数，然后映射
	static const int maxn_trie_01 = 100010;
	static const int max_log_trie_01 = 25;
	int id = 2; // 一开始的ID就是2
	int ch[maxn_trie_01 * max_log_trie_01][2];
	int sz[maxn_trie_01 * max_log_trie_01];

	int newNode() {
		ch[id][0] = ch[id][1] = sz[id] = 0;
		return id++;
	}
	// insert(x,1)就是插入，insert(x,-1)就是删除
	void insert(int x, int d) {
		int u = 1;
		for (int i = max_log_trie_01 - 1; i >= 0; --i) {
			int v = (x >> i) & 1;
			if (!ch[u][v]) ch[u][v] = newNode();
			u = ch[u][v];
			sz[u] += d; // sz[1]=0
		}
	}
	// 查找排名为k的数
	int kth(int k) {
		int u = 1;
		int x = 0;
		for (int i = max_log_trie_01 - 1; i >= 0; --i) {
			if (sz[ch[u][0]] >= k) u = ch[u][0];
			else {
				x |= (1 << i);
				k -= sz[ch[u][0]];
				u = ch[u][1];
			}
		}
		return x;
	}
	// 查找x的排名（此处排名是从0开始的，所以后面要加一）
	int nlt(int x) {
		int ans = 0;
		int u = 1;
		for (int i = max_log_trie_01 - 1; i >= 0; --i) {
			if ((x >> i) & 1) {
				ans += sz[ch[u][0]];
				u = ch[u][1];
			}
			else {
				u = ch[u][0];
			}
			if (!u) break;
		}
		return ans;
	}
	// 查找x的前驱
	int pre(int x) {
		return kth(nlt(x));
	}
	// 查找x的后继
	int next(int x) {
		return kth(nlt(x + 1) + 1);
	}
};
// splay树的实现比较简单，并且splay十分强大（可以操作区间），所以第二个实现的是splay树。
struct Splay {
	static const int splay_maxn = 100005;
	int rt = 0, tot = 0;
	int fa[splay_maxn], ch[splay_maxn][2], val[splay_maxn], cnt[splay_maxn], sz[splay_maxn];

	// 更新大小的操作
	void update(int x) {
		sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x];
	}
	// 判断x是父节点的左儿子还是右儿子
	bool get(int x) { return x == ch[fa[x]][1]; }
	// 销毁节点x
	void clear(int x) {
		ch[x][0] = ch[x][1] = fa[x] = val[x] = cnt[x] = sz[x] = 0;
	}
	// 旋转操作，和treap是一样的，但是这里多了维护father的关系，所以代码量多了很多
	void rotate(int x) {
		int y = fa[x], z = fa[y], chk = get(x);
		// 第一步把x对应的儿子放到y上，同时修改儿子的father
		ch[y][chk] = ch[x][chk ^ 1];
		if (ch[x][chk ^ 1]) fa[ch[x][chk ^ 1]] = y;
		// 调换父子关系
		ch[x][chk ^ 1] = y;
		fa[y] = x;
		// 调换祖父和子孙关系
		fa[x] = z;
		if (z) ch[z][y == ch[z][1]] = x;
		// 更新操作
		update(y);
		update(x);
	}
	// splay操作，splay树利用局部性原理，要求每一次操作x之后都强制将其splay到根节点
	// 总共有6中旋转的情况（x和fa[x]在左侧还是右侧决定），zig-zig,zig-zag,zig,zag,zag-zag,zag-zig
	// fa[x]=f,如果f和x在同侧就先旋转父节点然后旋转x节点，否则旋转两次x节点
	// splay是核心操作，在这一个过程中，根到x的路径都会被更新信息
	void splay(int x) {
		for (int f = fa[x]; f = fa[x], f; rotate(x))
			if (fa[f]) rotate(get(x) == get(f) ? f : x);
		rt = x;
	}
	// 插入过程，找到插入值的地方记得更新父亲和自己的信息然后进行splay操作
	void insert(int x) {
		if (!rt) {
			// 这是一棵空树
			val[++tot] = x;
			cnt[tot]++;
			rt = tot;
			update(rt);
			return;
		}
		int cur = rt, f = 0;
		while (true) {
			if (val[cur] == x) {
				++cnt[cur];
				update(cur);
				update(f);
				splay(cur);
				break;
			}
			f = cur;
			cur = ch[cur][val[cur] < x];
			if (!cur) {
				val[++tot] = x;
				++cnt[tot];
				fa[tot] = f;
				ch[f][val[f] < x] = tot;
				update(tot);
				update(f);
				splay(tot);
				break;
			}
		}
	}
	// 查询x的排名，查找到结果不要忘记splay
	int rank(int x) {
		int res = 0, cur = rt;
		while (true) {
			if (x < val[cur]) cur = ch[cur][0];
			else {
				res += sz[ch[cur][0]];
				if (x == val[cur]) {
					splay(cur);
					return res + 1;
				}
				res += cnt[cur];
				cur = ch[cur][1];
			}
		}
	}
	// 插入和删除在splay里面都是比较复杂的操作
	void del(int x) {
		// 首先将x旋转到根上面
		rank(x);
		if (cnt[rt] > 1) {
			--cnt[rt];
			update(rt);
			return;
		}
		// 如果有多个x那么删除一个就可以了，否则要合并左右子树
		if (!ch[rt][0] && !ch[rt][1]) {
			clear(rt);
			rt = 0;
			return;
		}
		if (!ch[rt][0]) {
			// 根变为右子树的根
			int cur = rt;
			rt = ch[rt][1];
			fa[rt] = 0;
			clear(cur);
			return;
		}
		if (!ch[rt][1]) {
			// 根变成左子树的根
			int cur = rt;
			rt = ch[rt][0];
			fa[rt] = 0;
			clear(cur);
			return;
		}
		// 左右子树都不为空的时候，选择左子树的最大的数作为根，也就是根右儿子的前驱
		// 所有把左子树的最大数splay上来，然后修改和原来的右儿子的关系
		int cur = rt, k = pre();
		fa[ch[cur][1]] = k;
		ch[k][1] = ch[cur][1];
		clear(cur);
		update(rt);
	}
	// 查询排名为k的数
	int kth(int k) {
		int cur = rt;
		while (true) {
			if (ch[cur][0] && k <= sz[ch[cur][0]]) {
				cur = ch[cur][0];
			}
			else {
				k -= (cnt[cur] + sz[ch[cur][0]]);
				if (k <= 0) {
					splay(cur);
					return val[cur];
				}
				cur = ch[cur][1];
			}
		}
	}
	// 查询前驱，操作等价于插入x之后，x就是根，那么前驱只要迭代查询即可，查询后继也是一样的
	// 最后记得将x删除然后splay即可
	int pre() {
		int cur = ch[rt][0];
		if (!cur) return cur;
		while (ch[cur][1]) cur = ch[cur][1]; // 一直往左子树的右子树找
		splay(cur);
		return cur;
	}
	int nxt() {
		int cur = ch[rt][1];
		if (!cur) return cur;
		while (ch[cur][0]) cur = ch[cur][0]; // 一直往右子树的左子树找
		splay(cur);
		return cur;
	}
};
// Splay的强大之处在于可以处理区间，这类问题主要就是根据索引建成splay树，然后插入两个虚点-inf和inf。
// 那么将l-1旋转到根上面，r+1旋转到根的右儿子上，那么r+1的左子树表示的就是区间[l,r]，就可以进行操作
// 具体的话就看具体的题目吧，反正这东西常数挺大的，除非限制死了，一般不用，RMQ通常是更好的选择。

// 下面是力扣中的链表题的总结，我觉得官方最优解的写法很不简单，于是做一个大总结。
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class ListProblem {
	// 迭代双链表进行加法运算（如果是逆序两数相加的话就需要使用栈）
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* head = nullptr, * tail = nullptr;
		int carry = 0; // 进位设置
		while (l1 || l2) {
			int n1 = l1 ? l1->val : 0;
			int n2 = l2 ? l2->val : 0;
			int sum = n1 + n2 + carry;
			if (!head) {
				head = tail = new ListNode(sum % 10);
			}
			else {
				tail->next = new ListNode(sum % 10);
				tail = tail->next;
			}
			carry = sum / 10;
			// 有就往前动，没有原地就是0
			if (l1) l1 = l1->next;
			if (l2) l2 = l2->next;
		}
		// 这一步非常关键，很多时候会忽略这一步
		if (carry > 0) tail->next = new ListNode(carry);
		return head;
	}
	// 反转链表（经典的双指针迭代就可以了，一前一后）
	// 从原来的链表上看，prev指向末尾的一个节点，cur是后续的下一个节点（这个性质很有用）
	ListNode* reverseList(ListNode* head) {
		ListNode* prev = nullptr;
		ListNode* curr = head;
		while (curr) {
			ListNode* next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		return prev;
	}
	ListNode* reverseBetween(ListNode* head, int left, int right) {
		// 只翻转固定的区间部分而不是整个链表
		// 当left=1的时候涉及到了头结点，所以需要哨兵
		ListNode* dummy = new ListNode(0, head);
		ListNode* p0 = dummy;
		for (int i = 0; i < left - 1; ++i) p0 = p0->next;
		ListNode* prev = nullptr;
		ListNode* cur = p0->next;
		// 下面的过程和翻转链表示一样的，这里只需要翻转right-left+1次
		for (int i = 0; i < right - left + 1; ++i) {
			ListNode* nxt = cur->next;
			cur->next = prev;
			prev = cur;
			cur = nxt;
		}
		// 调整前后关系
		p0->next->next = cur;
		p0->next = prev;
		return dummy->next;
	}
	ListNode* reverseKGroup(ListNode* head, int k) {
		// 这道题目意思就是说k个元素为一组然后翻转链表
		// 这道题和上面的区间翻转非常类似，只需要判断区间长度是否能翻转然后用临时变量存储p0即可
		ListNode* dummy = new ListNode(0, head);
		ListNode* p0 = dummy;
		ListNode* cur = head;
		int len = 0;
		while (cur) ++len, cur = cur->next;
		cur = p0->next;
		while (len >= k) {
			len -= k;
			// 初始化prev和cur
			ListNode* prev = nullptr;
			cur = p0->next;
			// 需要翻转k次链表
			for (int i = 0; i < k; i++) {
				ListNode* nxt = cur->next;
				cur->next = prev;
				prev = cur;
				cur = nxt;
			}
			// nxt存储的是下一次翻转的p0位置
			ListNode* nxt = p0->next;
			p0->next->next = cur;
			p0->next = prev;
			p0 = nxt;
		}
		return dummy->next;
	}
	// 合并链表的操作（合并两个有序的链表）
	// 可以使用递归操作，但是迭代的写法显然常数小很多
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
		// 这是一个哨兵节点
		ListNode* preHead = new ListNode(-1);
		ListNode* prev = preHead;
		// 迭代开始直到有一方到达了nullptr
		while (list1 != nullptr && list2 != nullptr) {
			if (list1->val > list2->val) {
				prev->next = list2;
				list2 = list2->next;
			}
			else {
				prev->next = list1;
				list1 = list1->next;
			}
			prev = prev->next;
		}
		// 合并之后最多只有一个还没有合并完，直接合并就可以了
		prev->next = (list1 == nullptr) ? list2 : list1;
		return preHead->next;
	}
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		// 合并K个有序链表，朴素做法是使用两两合并，但是这样的话链表会很长，复杂度很高
		// 根据合并两个有序链表的思想，我们可以使用一个优先队列维护最小值
		// 或者使用类似于归并排序的思想来进行操作，两两合并（因为这样做的话链表长度不会很长）
		function<ListNode*(int, int)> merge = [&](int l, int r) -> ListNode* {
			if (l == r) return lists[l];
			if (l > r) return nullptr;   // 注意这里的特判
			int mid = (l + r) >> 1;
			return mergeTwoLists(merge(l, mid), merge(mid + 1, r));
		};
		return merge(0, lists.size() - 1);
	}
	// 删除链表中的节点，有很多脑筋急转弯的题目
	// 哨兵技巧：一般适用于头结点被操作的链表题目
	// 删除倒数第N个节点（技巧是使用距离双指针同步移动）
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		// 哨兵节点
		ListNode* dummy = new ListNode(0, head);
		ListNode* right = head;
		ListNode* left = dummy;
		while (n--) right = right->next;
		while (right) {
			right = right->next;
			left = left->next;
		}
		left->next = left->next->next;
		ListNode* ans = dummy->next;
		delete dummy; // 释放内存
		return ans;
	}
	// 删除所有的重复出现的元素，因为可能删除头结点，所以需要哨兵
	ListNode* deleteDuplicates(ListNode* head) {
		ListNode* dummy = new ListNode(0, head);
		ListNode* cur = dummy;
		// 如果下一个和下下一个的值相同，我们就应该循环删除所有的重复节点
		while (cur->next && cur->next->next) {
			int w = cur->next->val;
			if (cur->next->next->val == w) {
				while (cur->next && cur->next->val == w)
					cur->next = cur->next->next;
			}
			else cur = cur->next;
		}
		ListNode* ans = dummy->next;
		delete dummy;
		return ans;
	}
	// 快慢指针的技巧（不是同步指针了），通常适用于环形链表
	ListNode* middleNode(ListNode* head) {
		// 最经典的运用，使用快慢指针寻找链表的中间节点
		ListNode *slow = head, * fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}
	bool hasCycle(ListNode* head) {
		// 快慢指针的另一个经典运用：判环
		// 快指针相对于慢指针的速度是1，那么如果存在环，那么一定存在某时刻，fast=slow
		ListNode* slow = head, * fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) return true;
		}
		return false;
	}
	ListNode* detectCycle(ListNode* head) {
		// 这道题有一个结论：快慢指针相遇时，慢指针一定没有走完整个环，这个很容易证明，忽略。
		// 当快慢指针相遇时，有一个结论，这时候慢指针和头指针同步移动，相遇的地方就是环开始的地方。
		// 具体的证明为：
		/*
			设头结点距离环起始a，环起始距离相遇地方b，环长为b+c。
			那么dis(fast)=a+k(b+c)，dis(slow)=a+b,dis(fast)=2*dis(slow)
			那么可以得到(a-c)=(k-1)(b+c)，表明当slow指针和head指针同时走c距离时，头指针与环起始
			的地方相差环长的整数倍，显然继续走下去会在环开始的地方相遇。
		*/
		ListNode* slow = head, * fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) {
				while (slow != head) {
					slow = slow->next;
					head = head->next;
				}
				return slow;
			}
		}
		return nullptr;
	}
};
// 链表的应用型难题很多，使用链表来设计数据结构也是经常出现的（第二天更新）
// 经典的就是设计LRU,LFU和一些O(1)的数据结构，经典套路就是哈希表+双向链表
// 这部分的算法由于不具有通用性，所以这里不打算实现，并且通常来说这些题目的难度很大