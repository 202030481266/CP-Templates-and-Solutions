// https://www.luogu.com.cn/problem/P3919


template<typename T>
struct PersistentArray { // 0 - index
	struct node {
		node* l, * r;
		T x;
	};
	int n = 1;
	vector<node*> root;
	int build(vector<T> v) {
		while (n < v.size()) n <<= 1;
		root.push_back(build(0, n - 1, v));
		return root.size() - 1;
	}
	node* build(int l, int r, vector<T>& v) {
		node* cur = new node();
		if (l == r) {
			if (l < v.size()) cur->x = v[l];
			else cur->x = 0;
		}
		else {
			int mid = (l + r) >> 1;
			cur->l = build(l, mid, v);
			cur->r = build(mid + 1, r, v);
		}
		return cur;
	}
	T get_val(int r, int i) {
		return get_val(root[r], i, 0, n - 1);
	}
	T get_val(node* cur, int i, int l, int r) {
		if (l == r) return cur->x;
		int mid = (l + r) >> 1;
		if (i <= mid) return get_val(cur->l, i, l, mid);
		else return get_val(cur->r, i, mid + 1, r);
	}
	// 修改第 i 个元素为 x，返回新的版本
	int upd(int r, int i, T x) {
		root.push_back(upd(root[r], i, x, 0, n - 1));
		return root.size() - 1;
	}
	node* upd(node* pre, int i, T x, int l, int r) {
		node* cur = new node();
		if (l == r) cur->x = x;
		else {
			int mid = (l + r) >> 1;
			if (i <= mid) {
				cur->l = upd(pre->l, i, x, l, mid);
				cur->r = pre->r;
			}
			else {
				cur->r = upd(pre->r, i, x, mid + 1, r);
				cur->l = pre->l;
			}
		}
		return cur;
	}
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> array(n);
    for (int i = 0; i < n; ++i) cin >> array[i];
    // 构建可持久化数组
    PersistentArray<int> pa;
    pa.build(array);
    while (m--) {
        int version, type, loc, value;
		cin >> version >> type >> loc;
		--loc;
        if (type == 1) {
			cin >> value;
            pa.upd(version, loc, value);
        }
        else {
            cout << pa.get_val(version, loc) << '\n';
            // 复制一份
            pa.root.push_back(pa.root[version]);
        }
    }
    return 0;
    
}


