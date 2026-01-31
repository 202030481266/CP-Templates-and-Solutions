// xiaoshulin
// 2023.12.10
typedef long long ll;
class UnionFind {
public:
	// [left, right]
    vector<int> parent, size, left, right;
	vector<ll> val;
	int n, setCount;
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1), val(_n), left(_n), right(_n) {
        iota(parent.begin(), parent.end(), 0);
		iota(left.begin(), left.end(), 0);
		iota(right.begin(), right.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (size[x] < size[y]) swap(x, y);
		// small set unite into big set, y -> x
        parent[y] = x;
        size[x] += size[y];
        --setCount;
		left[x] = min(left[x], left[y]);  // update the lower bound
		right[x] = max(right[x], right[y]); // update the upper bound
		val[x] |= val[y]; // update the value
        return true;
    }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
class Solution {
public:
    long long ringGame(vector<long long>& challenge) {
		int n = challenge.size();

		// x | a | a = x | a, so the number isn't important
		int n2 = n * 2;
		// use list will be faster

		UnionFind un(n2);
		// seems that the answer can not binary search
		// because the smaller may be stronger after or operation
		auto check = [&](ll value) -> bool {
			iota(un.parent.begin(), un.parent.end(), 0);
			iota(un.left.begin(), un.left.end(), 0);
			iota(un.right.begin(), un.right.end(), 0);
			fill(un.size.begin(), un.size.end(), 1);
			un.setCount = n2;
			for (int i = 0; i < n2; ++i)
				un.val[i] = challenge[i % n];
			int i = 0;
			while (i < n2) {
				// can expand
				if (challenge[i % n] <= value) {
					int lower = i - 1, upper = i + 1;
					ll cur = value | challenge[i % n], x = -1, y = -1; 
					bool flag = true;
					while ((lower >= 0 || upper < n2) && flag) {
						flag = false;
						x = -1, y = -1;
						if (lower >= 0) x = un.find(lower);
						if (upper < n2) y = un.find(upper);
						if (x != -1 && un.val[x] <= cur) { 
							cur |= un.val[x];
							un.unite(x, i);
							int f = un.find(i);
							lower = un.left[f] - 1;
							flag = true; // have update
						}
						if (y != -1 && un.val[y] <= cur) {
							cur |= un.val[y];
							un.unite(y, i);
							int f = un.find(i);
							upper = un.right[f] + 1;
							flag = true; // hvae update
						}
					}
					int f = un.find(i);
					i = un.right[f] + 1;
				}
				else ++i;
			}
			// [0, n2)
			return un.setCount == 1;
		};
		
		// binary search at the bit
		ll ans = 0, high = 0;
		for (int i = 0; i < n; ++i) {
			high = max(high, 63ll - __builtin_clzll(challenge[i]));
		}
		high = (1ll << high);
		ll res = high;
		while (high) {
			high >>= 1;
			if (!check(res | (high - 1))) res |= high;
		}
		return res;
    }
};


// use double list 
using ll = long long;
struct Node {
    ll v;
    Node *pre, *nxt;
    void erase() {
        this->nxt->pre = this->pre;
        this->pre->nxt = this->nxt;
    }
};

class Solution {
public:
    long long ringGame(vector<long long>& arr) {
        int n = size(arr);
        if (n == 1) return arr[0];
        // 使用节点池而不是每次新创建节点（每次新创建节点会tle）
        vector<Node *> nodes(n);
        for (auto &node: nodes) node = new Node();
        auto chk = [&](ll k) -> bool {
            Node *start = nullptr, *pre = nullptr, *cur;
            for (int i = 0; i < n; ++i) {
                cur = nodes[i];
                cur->v = arr[i];
                cur->pre = pre;
                if (i == 0) start = cur;
                if (pre) pre->nxt = cur;
                pre = cur;
            }
            pre->nxt = start, start->pre = pre;
            cur = start;
            do {
                if (k < cur->v) {
                    cur = cur->nxt;
                    continue;
                }
                cur->v |= k;
                while ((cur->nxt != cur && cur->nxt->v <= cur->v) || (cur->pre != cur && cur->pre->v <= cur->v)) {
                    while (cur->nxt != cur && cur->nxt->v <= cur->v) {
                        cur->v |= cur->nxt->v;
                        if (cur->nxt == start) start = start->nxt;
                        cur->nxt->erase();

                    }
                    while (cur->pre != cur && cur->pre->v <= cur->v) {
                        cur->v |= cur->pre->v;
                        if (cur->pre == start) start = start->nxt;
                        cur->pre->erase();
                    }
                }
                cur = cur->nxt;
            } while (cur != start);
            return start == start->pre;
        };
        ll ans = 0, mx = 0;
        for (auto x: arr) mx = max(mx, __lg(x));
        ans = (1ll << (mx + 1)) - 1;
        for (ll i = 1ll << mx; i; i >>= 1) {
            if (chk(ans ^ i)) ans ^= i;
        }
        return ans;
    }
};
