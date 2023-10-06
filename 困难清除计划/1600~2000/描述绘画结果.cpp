// https://leetcode.cn/problems/describe-the-painting/


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
class Solution {
public:
	static constexpr int N = 100010;
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
    	Fenwick<long long> tree1(N);
    	Fenwick<long long> tree2(N);
    	vector<int> pos;
    	vector<vector<long long>> ans;
    	vector<vector<long long>> res;

    	set<int> s;
    	for (auto c : segments) {
    		long long l = c[0], r = c[1], v = c[2];
    		tree1.update(l, v);
    		tree1.update(r, -v);
    		tree2.update(l, (l - 1) * v);
    		tree2.update(r, -(r - 1) * v);
    		s.emplace(l);
    		s.emplace(r);
    	}
    	auto f = [&](int l, int r) {
    		// [l, r]
    		long long sl = (l - 1) * tree1.query(l) - tree2.query(l);
    		long long sr = r * tree1.query(r + 1) - tree2.query(r + 1);
            cout << l << ' ' << r << ' ' << sr - sl << endl;
    		return sr - sl;
    	};
    	for (auto v : s) pos.emplace_back(v);
    	for (int i = 0; i < pos.size() - 1; ++i) {
    		int l = pos[i], r = pos[i + 1];
    		long long sum = f(l, r - 1);
            if (sum > 0)
    		    res.emplace_back(vector<long long>{l, r, sum / (r - l)});
    	}
    	return res;
    }
};